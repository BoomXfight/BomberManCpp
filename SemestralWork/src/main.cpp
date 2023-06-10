#include "Singletons/Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    float FPS = 60;
    int DELAY_TIME = 1000.0f / FPS;
    Uint32 frameStart, frameTime;

    std::cout << "Game init attempt." << std::endl;
    if(TheGame::Instance()->init("BomberMan", 0, 0, 960, 540, false))
    {
        std::cout << "Game init success!" << std::endl;
        while(TheGame::Instance()->isRunning()) // Game loop
        {
            frameStart = SDL_GetTicks();

            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            // Fewer FPS during menu states to prevent double clicks
            if(TheGame::Instance()->getStateMachine()->mGameStates.back()->getStateID() == "MAIN_MENU_STATE"
            || TheGame::Instance()->getStateMachine()->mGameStates.back()->getStateID() == "SCOREBOARD_MENU_STATE"
            || TheGame::Instance()->getStateMachine()->mGameStates.back()->getStateID() == "SINGLE_PLAYER_MENU_STATE"
            || TheGame::Instance()->getStateMachine()->mGameStates.back()->getStateID() == "MULTI_PLAYER_MENU_STATE"
            || TheGame::Instance()->getStateMachine()->mGameStates.back()->getStateID() == "PAUSE_MENU_STATE"
            || TheGame::Instance()->getStateMachine()->mGameStates.back()->getStateID() == "SINGLE_PLAYER_WON_STATE"
            || TheGame::Instance()->getStateMachine()->mGameStates.back()->getStateID() == "SINGLE_PLAYER_LOST_STATE"
            || TheGame::Instance()->getStateMachine()->mGameStates.back()->getStateID() == "MULTI_PLAYER1_WIN_STATE"
            || TheGame::Instance()->getStateMachine()->mGameStates.back()->getStateID() == "MULTI_PLAYER2_WIN_STATE")
            {
                FPS = 20;
                DELAY_TIME = 1000.0f / FPS;
            }

            frameTime = SDL_GetTicks() - frameStart;
            if(frameTime < DELAY_TIME) // Takes care of a stable framerate
                SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }
    else
    {
        std::cout << "Game init failure: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "Game closing." << std::endl;
    TheGame::Instance()->clean();
    return 0;
}
