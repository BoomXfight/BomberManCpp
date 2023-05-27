#pragma once
#include "SDL2/SDL.h"
#include "GameObject.hpp"
#include "GameStateMachine.hpp"
#include <vector>
#include <memory>

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
    void setP1(std::string s);
    void setP2(std::string s);
    bool P1Ready();
    bool P2Ready();
    std::string getP1() {return player1;}
    std::string getP2() {return player2;}
    bool isRunning();
    GameStateMachine* getStateMachine();


private:
    Game();
    ~Game();
    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_currentFrame;
    bool m_bRunning;

    std::string player1;
    std::string player2;

    std::vector<GameObject*> m_gameObjects;
    GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;