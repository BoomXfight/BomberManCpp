#include "MainMenuState.hpp"
#include "TextureManager.hpp"
#include "MenuButton.hpp"
#include "StaticObject.hpp"
#include "SinglePlayerMenuState.hpp"
#include "MultiPlayerMenuState.hpp"
#include "Game.hpp"
#include "SDL2/SDL.h"
#include <iostream>

const std::string MainMenuState::s_menuID = "MainMenu";

void MainMenuState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MainMenuState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter()
{
    if(!TheTextureManager::Instance()->load("../Assets/BomberManLogo.png", "BomberMan", TheGame::Instance()->getRenderer())
        || !TheTextureManager::Instance()->load("../Assets/Bomber.png", "Bomber", TheGame::Instance()->getRenderer())
        || !TheTextureManager::Instance()->load("../Assets/SinglePlayerButton.png", "SinglePlayer", TheGame::Instance()->getRenderer())
        || !TheTextureManager::Instance()->load("../Assets/MultiPlayer.png", "MultiPlayer", TheGame::Instance()->getRenderer())
        || !TheTextureManager::Instance()->load("../Assets/ScoreBoard.png", "ScoreBoard", TheGame::Instance()->getRenderer())
        || !TheTextureManager::Instance()->load("../Assets/Exit.png", "Exit", TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load the button :" << SDL_GetError() << "\n";
        return false;
    }

    GameObject* bomberMan = new StaticObject(new LoaderParams(50, 20, 600, 166, "BomberMan"));
    GameObject* bomber = new StaticObject(new LoaderParams(530, 240, 325, 250, "Bomber"));
    GameObject* singlePlayer = new MenuButton(new LoaderParams(180, 210, 250, 80, "SinglePlayer"), menuToSinglePlayer);
    GameObject* multiPlayer = new MenuButton(new LoaderParams(180, 310, 220, 80, "MultiPlayer"), menuToMultiPlayer);
    GameObject* scoreBoard = new MenuButton(new LoaderParams(180, 410, 190, 80, "ScoreBoard"), menuToSinglePlayer);
    GameObject* exit = new MenuButton(new LoaderParams(830, 60, 90, 50, "Exit"), menuToQuit);

    m_gameObjects.push_back(bomberMan);
    m_gameObjects.push_back(bomber);
    m_gameObjects.push_back(singlePlayer);
    m_gameObjects.push_back(multiPlayer);
    m_gameObjects.push_back(scoreBoard);
    m_gameObjects.push_back(exit);
    std::cout << "entering MenuState\n";
    return true;
}

bool MainMenuState::onExit()
{
    TheGame ::Instance()->setP1(""); // Reset the player names
    TheGame ::Instance()->setP2("");

    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("BomberMan");
    TheTextureManager::Instance()->clearFromTextureMap("Bomber");
    TheTextureManager::Instance()->clearFromTextureMap("SinglePlayer");
    TheTextureManager::Instance()->clearFromTextureMap("MultiPlayer");
    TheTextureManager::Instance()->clearFromTextureMap("ScoreBoard");
    TheTextureManager::Instance()->clearFromTextureMap("Exit");
    std::cout << "exiting MenuState\n";
    return true;
}

void MainMenuState::menuToSinglePlayer()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerMenuState());
}

void MainMenuState::menuToMultiPlayer()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerMenuState());
};

void MainMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}
