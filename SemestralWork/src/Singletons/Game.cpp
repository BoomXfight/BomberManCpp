#include <iostream>
#include "Game.hpp"
#include "InputHandler.hpp"
#include "GameObjectFactory.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../GameObjects/Player1.hpp"
#include "../GameObjects/Player2.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "../GameStates/MainMenuState.hpp"

Game* Game::Instance()
{
    if(mInstance == nullptr)
       mInstance = new Game();

    return mInstance;
}

/**
 * This method initializes the game
 * @param[in] pTitle
 * @param[in] pX_WindowPos
 * @param[in] pY_WindowPos
 * @param[in] pWindowWidth
 * @param[in] pWindowHeight
 * @param[in] pFullscreen
 * @return true -> Game initialization success, false -> Failed to initialize the game
 */
bool Game::init(const char* pTitle, int pX_WindowPos, int pY_WindowPos, int pWindowWidth, int pWindowHeight,
                bool pFullscreen)
{
    if(SDL_Init(SDL_INIT_VIDEO) == 0) // SDL_INIT_EVERYTHING
    {
        int flags = 0;
        if(pFullscreen)
            flags = SDL_WINDOW_FULLSCREEN;

        std::cout << "SDL init success." << std::endl;

        mGameWidth = pWindowWidth;
        mGameHeight = pWindowHeight;
        mWindow = SDL_CreateWindow(pTitle, pX_WindowPos, pY_WindowPos,mGameWidth, mGameHeight, flags);
        if(mWindow != nullptr)
        {
            std::cout << "Window creation success." << std::endl;
            mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
            if(mRenderer != nullptr)
            {
                std::cout << "Renderer creation success." << std::endl;
                SDL_SetRenderDrawColor(mRenderer,0,0,0,255);
            }
            else
            {
                std::cout << "Renderer init fail: " << SDL_GetError() << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "Window init fail: " << SDL_GetError() << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "SDL init fail: " << SDL_GetError() << std::endl;
        return false;
    }

    //Register game objects for TheGameObjectFactory
    TheGameObjectFactory ::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory ::Instance()->registerType("Player1", new Player1Creator());
    TheGameObjectFactory ::Instance()->registerType("Player2", new Player2Creator());
    TheGameObjectFactory ::Instance()->registerType("StaticObject", new StaticObjectCreator());
    TheGameObjectFactory ::Instance()->registerType("TextSquare", new TextSquareCreator());

    //Begin with mainMenuState
    mGameStateMachine = new GameStateMachine();
    mGameStateMachine->changeState(new MainMenuState());

    std::cout << "Init success." << std::endl;
    mIsRunning = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(mRenderer);
    mGameStateMachine->render(); // rendering current game state
    SDL_RenderPresent(mRenderer); // draw to the screen
}

void Game::update()
{
    mGameStateMachine->update(); // updating current game state
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update(); // event handling current game state
}

void Game::clean()
{
    std::cout << "Cleaning the game" << std::endl;
    TheInputHandler::Instance()->clean();
    TheGame::Instance()->mIsRunning = false;
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::quit()
{
    mIsRunning = false;
}

void Game::setP1(std::string s)
{
    mPlayer1 = s;
}

void Game::setP2(std::string s)
{
    mPlayer2 = s;
}

bool Game::P1Ready()
{
    return(!mPlayer1.empty());
}

bool Game::P2Ready()
{
    return(!mPlayer2.empty());
}

bool Game::isRunning()
{
    return mIsRunning;
}

std::string Game::getP1() const
{
    return mPlayer1;
}

std::string Game::getP2() const
{
    return mPlayer2;
}

SDL_Renderer* Game::getRenderer() const
{
    return mRenderer;
}

GameStateMachine* Game::getStateMachine() const
{
    return mGameStateMachine;
}

int Game::getGameWidth() const
{
    return mGameWidth;
}

int Game::getGameHeight() const
{
    return mGameHeight;
}

Game::~Game() {}

Game::Game() {}

Game* Game::mInstance = nullptr;
