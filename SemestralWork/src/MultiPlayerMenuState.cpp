#include "MultiPlayerMenuState.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "StaticObject.hpp"
#include "MenuButton.hpp"
#include "MainMenuState.hpp"
#include <iostream>

void MultiPlayerMenuState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

void MultiPlayerMenuState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

bool MultiPlayerMenuState::onEnter()
{
    if(!TheTextureManager::Instance()->load("../Assets/MultiPlayerHeading.png", "MultiPlayer", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Exit.png", "Exit", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Back.png", "Back", TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load the button :" << SDL_GetError() << "\n";
        return false;
    }

    GameObject* multiPlayer = new StaticObject(new LoaderParams(150, 20, 660, 166, "MultiPlayer"));
    GameObject* exit = new MenuButton(new LoaderParams(840, 40, 90, 50, "Exit"), menuToQuit);
    GameObject* back = new MenuButton(new LoaderParams(30, 40, 90, 50, "Back"), SpMenuToMainMenu);

    m_gameObjects.push_back(multiPlayer);
    m_gameObjects.push_back(exit);
    m_gameObjects.push_back(back);

    std::cout << "entering SinglePlayerMenu state\n";
    return true;
}

bool MultiPlayerMenuState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("MultiPlayer");
    TheTextureManager::Instance()->clearFromTextureMap("Exit");
    TheTextureManager::Instance()->clearFromTextureMap("Back");
    std::cout << "exiting SinglePlayerMenuState\n";
    return true;
}

void MultiPlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

void MultiPlayerMenuState::SpMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}
