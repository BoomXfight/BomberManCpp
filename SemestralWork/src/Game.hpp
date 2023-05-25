#pragma once
#include "SDL2/SDL.h"
#include "vector"
#include "GameObject.hpp"
#include "GameStateMachine.hpp"

class Game
{
public:
    static Game* Instance();
    SDL_Renderer* getRenderer() const;
    bool init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    void quit();
    bool isRunning();

private:
    Game();
    ~Game();
    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_currentFrame;
    bool m_bRunning;

    std::vector<GameObject*> m_gameObjects;
    GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;