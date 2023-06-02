#include "TextureManager.hpp"
#include <iostream>

TextureManager* TextureManager::Instance()
{
    if(mInstance == 0)
        mInstance = new TextureManager();

    return mInstance;
}

/**
 * This method loads an image from file and stores it into the textureMap
 * @param[in] fileName
 * @param[in] identifier
 * @param[in] pRenderer
 * @return true -> success, false -> failure
 */
bool TextureManager::load(const std::string& pFileName, const std::string& pIdentifier, SDL_Renderer* pRenderer)
{
    SDL_Surface* tmpSurface = IMG_Load(pFileName.c_str());
    if(tmpSurface == 0)
    {
        std::cout << "Failed to load the texture: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    if(texture != 0)
    {
        mTextureMap[pIdentifier] = texture;
        return true;
    }
    return false;
}

/**
 * This method draws an entire texture on the screen
 * @param[in] pIdentifier
 * @param[in] pX
 * @param[in] pY
 * @param[in] pWidth
 * @param[in] pHeight
 * @param[in] pRenderer
 * @param[in] pFlip
 */
void TextureManager::draw(const std::string& pIdentifier, int pX, int pY, int pWidth, int pHeight,
                          SDL_Renderer* pRenderer, SDL_RendererFlip pFlip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = pWidth;
    srcRect.h = destRect.h = pHeight;
    destRect.x = pX;
    destRect.y = pY;
    SDL_RenderCopyEx(pRenderer, mTextureMap[pIdentifier], &srcRect, &destRect, 0,
                     nullptr, pFlip);
}

/**
 * This method draws part of the texture to the screen
 * Fit for drawing sprites and animations
 * @param[in] pIdentifier
 * @param[in] pX
 * @param[in] pY
 * @param[in] pWidth
 * @param[in] pHeight
 * @param[in] pCurrentRow
 * @param[in] pCurrentFrame
 * @param[in] pRenderer
 * @param[in] pFlip
 */
void TextureManager::drawFrame(const std::string& pIdentifier, int pX, int pY, int pWidth, int pHeight, int pCurrentRow,
                               int pCurrentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip pFlip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = pWidth * pCurrentFrame;
    srcRect.y = pHeight * (pCurrentRow - 1);
    srcRect.w = destRect.w = pWidth;
    srcRect.h = destRect.h = pHeight;
    destRect.x = pX;
    destRect.y = pY;
    SDL_RenderCopyEx(pRenderer, mTextureMap[pIdentifier], &srcRect, &destRect, 0,
                     0, pFlip);
}

/**
 * This method is used to draw a tile from a tileSet to the screen
 * @param[in] pIdentifier
 * @param[in] pMargin
 * @param[in] pSpacing
 * @param[in] pX
 * @param[in] pY
 * @param[in] pWidth
 * @param[in] pHeight
 * @param[in] pCurrentRow
 * @param[in] pCurrentFrame
 * @param[in] pRenderer
 */
void TextureManager::drawTile(const std::string& pIdentifier, int pMargin, int pSpacing, int pX, int pY, int pWidth,
                              int pHeight, int pCurrentRow, int pCurrentFrame, SDL_Renderer *pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = pMargin + (pSpacing + pWidth) * pCurrentFrame;
    srcRect.y = pMargin + (pSpacing + pHeight) * pCurrentRow;
    srcRect.w = destRect.w = pWidth;
    srcRect.h = destRect.h = pHeight;
    destRect.x = pX;
    destRect.y = pY;
    SDL_RenderCopyEx(pRenderer, mTextureMap[pIdentifier], &srcRect,&destRect, 0,
                     nullptr, SDL_FLIP_NONE);
}


void TextureManager::clearFromTextureMap(const std::string& pIdentifier)
{
    mTextureMap.erase(pIdentifier);
}

TextureManager::TextureManager() {};

TextureManager* TextureManager::mInstance = 0;
