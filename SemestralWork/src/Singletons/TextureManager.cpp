#include "TextureManager.hpp"
#include <iostream>

TextureManager* TextureManager::Instance()
{
    if(s_pInstance == 0)
    {
        s_pInstance = new TextureManager();
        return s_pInstance;
    }
    return s_pInstance;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if(pTempSurface == 0)
    {
        std::cout << "Failed to load the texture: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    if(pTexture != 0)
    {
        m_textureMap[id] = pTexture;
        return true;
    }
    return false; // If something went wrong
}

/**
 * This method draws an entire texture to the screen
 *
 * @param id
 * @param x
 * @param y
 * @param width
 * @param height
 * @param pRenderer
 * @param flip
 */
void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

/**
 *  * This method draws a certain part of the texture to the screen
 *
 * @param id
 * @param x
 * @param y
 * @param width
 * @param height
 * @param currentRow
 * @param currentFrame
 * @param pRenderer
 * @param flip
 */
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
                               SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
    m_textureMap.erase(id);
}

TextureManager* TextureManager::s_pInstance = 0;
