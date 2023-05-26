#include <iostream>
#include "Game.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"

SDL_Renderer* Game::getRenderer() const {return m_pRenderer;}

Game* Game::Instance()
{
    if(s_pInstance == 0)
    {
        s_pInstance = new Game();
        return s_pInstance;
    }
    return s_pInstance;
}

Game::~Game() {}

Game::Game() {}

bool Game::isRunning() {return m_bRunning;}

bool Game::init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen)
{
    if(SDL_Init(SDL_INIT_VIDEO) == 0) // SDL_INIT_EVERYTHING
    {
        int flags = 0;
        if(fullscreen)
            flags = SDL_WINDOW_FULLSCREEN;

        std::cout << "SDL init success\n";

        m_pWindow = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if(m_pWindow != 0)
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if(m_pRenderer != 0)
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);
            }
            else
            {
                std::cout << "renderer init fail: " << SDL_GetError() << '\n';
                return false;
            }
        }
        else
        {
            std::cout << "window init fail: " << SDL_GetError() << '\n';
            return false;
        }
    }
    else
    {
        std::cout << "SDL init fail: " << SDL_GetError() << '\n';
        return false;
    }

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

    std::cout << "init success\n";
    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color
    m_pGameStateMachine->render(); // rendering current game state
    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
    m_pGameStateMachine->update(); // updating current game state
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update(); // event handling current game state
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    TheInputHandler::Instance()->clean();
    TheGame::Instance()->m_bRunning = false;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::quit()
{
    m_bRunning = false;
}

GameStateMachine* Game::getStateMachine(){return m_pGameStateMachine;}

Game* Game::s_pInstance = 0;
