#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

class TextureManager
{
public:
    static TextureManager* Instance();
    bool load(const std::string& pFileName, const std::string& pIdentifier, SDL_Renderer* pRenderer);
    void draw(const std::string& pIdentifier, int pX, int pY, int pWidth, int pHeight,
              SDL_Renderer* pRenderer, SDL_RendererFlip pFlip = SDL_FLIP_NONE);
    void drawFrame(const std::string& pIdentifier, int pX, int pY, int pWidth, int pHeight, int pCurrentRow,
                   int pCurrentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip pFlip = SDL_FLIP_NONE);
    void drawTile(const std::string& pIdentifier, int pMargin, int pSpacing, int pX, int pY, int pWidth,
                  int pHeight, int pCurrentRow, int pCurrentFrame, SDL_Renderer *pRenderer);
    void drawText(std::string str, int pX, int pY, SDL_Color clr, SDL_Renderer *pRenderer, TTF_Font* pFont);
    void clearFromTextureMap(const std::string& pIdentifier);

private:
    TextureManager();
    static TextureManager* mInstance;
    std::map<std::string, SDL_Texture*> mTextureMap;
};

typedef TextureManager TheTextureManager;
