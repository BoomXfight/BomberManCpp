#include "TextureManager.hpp"
#include <iostream>

TextureManager* TextureManager::Instance()
{
    if(mInstance == nullptr)
        mInstance = new TextureManager();

    return mInstance;
}

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
                     nullptr, pFlip);
}

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

void TextureManager::drawText(std::string str, int pX, int pY, SDL_Color clr, SDL_Renderer *pRenderer, TTF_Font* pFont)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(pFont, str.c_str(), clr);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = textSurface->w;
    srcRect.h = destRect.h = textSurface->h;
    destRect.x = pX;
    destRect.y = pY;
    SDL_RenderCopyEx(pRenderer, textTexture, &srcRect,&destRect, 0, nullptr, SDL_FLIP_NONE);
}

void TextureManager::clearFromTextureMap(const std::string& pIdentifier)
{
    mTextureMap.erase(pIdentifier);
}

TextureManager::TextureManager() {};

TextureManager::~TextureManager()
{
    delete mInstance;
}

TextureManager* TextureManager::mInstance = nullptr;
