#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

/**
 * @class TextureManager
 * This singleton class is responsible for managing textures throughout the game.
 * It also allows for various rendering methods to render the texture to the screen.
 */
class TextureManager
{
public:
    static TextureManager* Instance();

    /**
     * This method loads an image from file and stores it into the textureMap
     * @param[in] fileName file to load from
     * @param[in] identifier
     * @param[in] pRenderer renderer to use
     * @return true -> success, false -> failure
     */
    bool load(const std::string& pFileName, const std::string& pIdentifier, SDL_Renderer* pRenderer);

    /**
     * This method draws an entire texture on the screen.
     * @param[in] pIdentifier
     * @param[in] pX
     * @param[in] pY
     * @param[in] pWidth
     * @param[in] pHeight
     * @param[in] pRenderer
     * @param[in] pFlip
     */
    void draw(const std::string& pIdentifier, int pX, int pY, int pWidth, int pHeight,
              SDL_Renderer* pRenderer, SDL_RendererFlip pFlip = SDL_FLIP_NONE);

    /**
     * This method draws part of the texture to the screen.
     * Use for drawing sprites and animations.
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
    void drawFrame(const std::string& pIdentifier, int pX, int pY, int pWidth, int pHeight, int pCurrentRow,
                   int pCurrentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip pFlip = SDL_FLIP_NONE);

    /**
     * This method is used to draw a tile from a tileSet to the screen.
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
    void drawTile(const std::string& pIdentifier, int pMargin, int pSpacing, int pX, int pY, int pWidth,
                  int pHeight, int pCurrentRow, int pCurrentFrame, SDL_Renderer *pRenderer);

    /**
     * This method renders a plain text to the screen.
     * @param str
     * @param pX
     * @param pY
     * @param clr
     * @param pRenderer
     * @param pFont
     */
    void drawText(std::string str, int pX, int pY, SDL_Color clr, SDL_Renderer *pRenderer, TTF_Font* pFont);

    /**
     * This method clears a specific texture from the texture map
     * @param pIdentifier
     */
    void clearFromTextureMap(const std::string& pIdentifier);

private:
    TextureManager();
    ~TextureManager();
    static TextureManager* mInstance;
    std::map<std::string, SDL_Texture*> mTextureMap;
};

typedef TextureManager TheTextureManager;
