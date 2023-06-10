#pragma once
#include "../GameObjects/GameObject.hpp"
#include "../GameStates/GameStateMachine.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <memory>

class Game
{
public:
    static Game* Instance();
    bool init(const char* pTitle, int pX_WindowPos, int pY_WindowPos, int pWindowWidth, int pWindowHeight,
              bool pFullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    void quit();
    void setP1(std::string s);
    void setP2(std::string s);
    bool P1Ready();
    bool P2Ready();
    bool isRunning();
    int getGameWidth() const;
    int getGameHeight() const;
    std::string getP1() const;
    std::string getP2() const;
    SDL_Renderer* getRenderer() const;
    GameStateMachine* getStateMachine() const;
    TTF_Font* getFont() const;

private:
    Game();

    static Game* mInstance;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;

    int mGameWidth;
    int mGameHeight;
    bool mIsRunning;

    std::string mPlayer1;
    std::string mPlayer2;

    GameStateMachine* mGameStateMachine;
};

typedef Game TheGame;
