#include "MenuButton.hpp"
#include "Player1.hpp"
#include "Player2.hpp"
#include "Enemy.hpp"
#include "StaticObject.hpp"
#include "TextSquare.hpp"
#include "MainMenuState.hpp"
#include "GameObjectFactory.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"

Game::~Game()
{
    delete mGameStateMachine;
}

Game* Game::Instance()
{
    if(mInstance == nullptr)
       mInstance = new Game();

    return mInstance;
}

bool Game::init(const char* pTitle, int pX_WindowPos, int pY_WindowPos, int pWindowWidth, int pWindowHeight,
                bool pFullscreen)
{
    if(SDL_Init(SDL_INIT_VIDEO) == 0) // SDL_INIT_EVERYTHING
    {
        int flags = 0;
        if(pFullscreen)
            flags = SDL_WINDOW_FULLSCREEN;

        mGameWidth = pWindowWidth;
        mGameHeight = pWindowHeight;
        std::cout << "SDL init success." << std::endl;

        if(TTF_Init() == 0)
        {
            try
            {
                mFont1 = TTF_OpenFont("assets/Fonts/RodchenkoBTT.ttf", 35);
                if (!mFont1)
                    throw std::runtime_error("Failed to load font.");
                    
                mFont2 = TTF_OpenFont("assets/Fonts/RodchenkoBTT.ttf", 30);
                if (!mFont2)
                    throw std::runtime_error("Failed to load font.");
                    
                mFont3 = TTF_OpenFont("assets/Fonts/RodchenkoBTT.ttf", 50);
                if (!mFont2)
                    throw std::runtime_error("Failed to load font.");
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                return false;
            }
            std::cout << "TTF init success." << std::endl;

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
            std::cout << "TTF init failed." << std::endl;
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
    TheGameObjectFactory ::Instance()->registerType("Enemy", new EnemyCreator());
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
    mGameStateMachine->render();
    SDL_RenderPresent(mRenderer);
}

void Game::update()
{
    mGameStateMachine->update();
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
}

void Game::clean()
{
    std::cout << "Cleaning the game." << std::endl;
    mIsRunning = false;
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    TTF_Quit();
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

int Game::getGameWidth() const
{
    return mGameWidth;
}

int Game::getGameHeight() const
{
    return mGameHeight;
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

TTF_Font* Game::getFont1() const
{
    return mFont1;
}

TTF_Font* Game::getFont2() const
{
    return mFont2;
}

TTF_Font* Game::getFont3() const
{
    return mFont3;
}

GameStateMachine* Game::getStateMachine() const
{
    return mGameStateMachine;
}

Game::Game() = default;

Game* Game::mInstance = nullptr;
