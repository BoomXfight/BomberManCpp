#pragma once
#include "SDL2/SDL.h"
#include "../GameObjects/GameObject.hpp"
#include "../GameStates/GameStateMachine.hpp"
#include <vector>
#include <memory>

class Game
{
public:
    static Game* Instance();
    bool init(const char* title, int x_WindowPos, int y_WindowPos, int windowWidth, int windowHeight, bool fullscreen);
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
    std::string getP1();
    std::string getP2();
    SDL_Renderer* getRenderer() const;
    GameStateMachine* getStateMachine() const;
    int getGameWidth() const;
    int getGameHeight() const;


private:
    Game();
    ~Game();
    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_pCurrentFrame;
    int m_pGameWidth;
    int m_pGameHeight;
    bool m_pIsRunning;

    std::string m_pPlayer1;
    std::string m_pPlayer2;

    std::vector<GameObject*> m_pGameObjects;
    GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;