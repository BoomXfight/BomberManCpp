#include <iostream>
#include "Game.hpp"
#include "InputHandler.hpp"
#include "GameObjectFactory.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../GameObjects/Player.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "../GameStates/MainMenuState.hpp"

Game* Game::Instance()
{
    if(s_pInstance == 0)
        s_pInstance = new Game();

    return s_pInstance;
}

/**
 * This method initializes the game
 * @param[in] title
 * @param[in] x_WindowPos
 * @param[in] y_WindowPos
 * @param[in] windowWidth
 * @param[in] windowHeight
 * @param[in] fullscreen
 * @return true -> success, false -> failure
 */
bool Game::init(const char* title, int x_WindowPos, int y_WindowPos, int windowWidth, int windowHeight, bool fullscreen)
{
    if(SDL_Init(SDL_INIT_VIDEO) == 0) // SDL_INIT_EVERYTHING
    {
        int flags = 0;
        if(fullscreen)
            flags = SDL_WINDOW_FULLSCREEN;

        std::cout << "SDL init success\n";

        m_pGameWidth = windowWidth;
        m_pGameHeight = windowHeight;

        m_pWindow = SDL_CreateWindow(title, x_WindowPos, y_WindowPos,
                                     m_pGameWidth, m_pGameHeight, flags);

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

    //Register game objects for TheGameObjectFactory
    TheGameObjectFactory ::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory ::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory ::Instance()->registerType("StaticObject", new StaticObjectCreator());
    TheGameObjectFactory ::Instance()->registerType("TextSquare", new TextSquareCreator());

    //Begin with mainMenuState
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

    std::cout << "init success\n";
    m_pIsRunning = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
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
    TheGame::Instance()->m_pIsRunning = false;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::quit()
{
    m_pIsRunning = false;
}

void Game::setP1(std::string s)
{
    m_pPlayer1 = s;
}

void Game::setP2(std::string s)
{
    m_pPlayer2 = s;
}

bool Game::P1Ready()
{
    return(m_pPlayer1.size()>0);
}

bool Game::P2Ready()
{
    return(m_pPlayer2.size()>0);
}

bool Game::isRunning()
{
    return m_pIsRunning;
}

std::string Game::getP1()
{
    return m_pPlayer1;
}

std::string Game::getP2()
{
    return m_pPlayer2;
}

SDL_Renderer* Game::getRenderer() const
{
    return m_pRenderer;
}

GameStateMachine* Game::getStateMachine() const
{
    return m_pGameStateMachine;
}

int Game::getGameWidth() const
{
    return m_pGameWidth;
}

int Game::getGameHeight() const
{
    return m_pGameHeight;
}

Game::~Game() {}

Game::Game() {}

Game* Game::s_pInstance = 0;
