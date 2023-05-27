#include <SDL2/SDL.h>
#include <iostream>
#include "Game.hpp"

int main(int argc, char* argv[])
{
    float FPS = 60;
    int DELAY_TIME = 1000.0f / FPS;
    Uint32 frameStart, frameTime;

    std::cout << "game init attempt...\n";
    if(TheGame::Instance()->init("BomberMan", 0, 0, 960, 540, false))
    {
        std::cout << "game init success!\n";
        while(TheGame::Instance()->isRunning()) // Game loop
        {
            frameStart = SDL_GetTicks();

            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            frameTime = SDL_GetTicks() - frameStart;
            if(TheGame::Instance()->getStateMachine()->m_gameStates.back()->getStateID() == "SinglePlayerMenu"
            || TheGame::Instance()->getStateMachine()->m_gameStates.back()->getStateID() == "MainMenu")
            {
                FPS = 10;
                DELAY_TIME = 1000.0f / FPS;
            }

            if(frameTime < DELAY_TIME) // Takes care of a 60 FPS
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }
    }
    else
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    std::cout << "game closing...\n";
    TheGame::Instance()->clean();
    return 0;
}


