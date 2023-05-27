#include "SinglePlayerMenuState.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "StaticObject.hpp"
#include "MenuButton.hpp"
#include "MainMenuState.hpp"
#include <iostream>

const std::string SinglePlayerMenuState::s_menuID = "SinglePlayerMenu";

void SinglePlayerMenuState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

void SinglePlayerMenuState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

bool SinglePlayerMenuState::onEnter()
{
    if(!TheTextureManager::Instance()->load("../Assets/SinglePlayerHeading.png", "SinglePlayer", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Exit.png", "Exit", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Back.png", "Back", TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load the button :" << SDL_GetError() << "\n";
        return false;
    }

    GameObject* singlePlayer = new StaticObject(new LoaderParams(150, 20, 660, 166, "SinglePlayer"));
    GameObject* exit = new MenuButton(new LoaderParams(840, 40, 90, 50, "Exit"), menuToQuit);
    GameObject* back = new MenuButton(new LoaderParams(30, 40, 90, 50, "Back"), SpMenuToMainMenu);

    m_gameObjects.push_back(singlePlayer);
    m_gameObjects.push_back(exit);
    m_gameObjects.push_back(back);

    std::cout << "entering SinglePlayerMenu state\n";
    return true;
}

bool SinglePlayerMenuState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("SinglePlayer");
    TheTextureManager::Instance()->clearFromTextureMap("Exit");
    std::cout << "exiting MenuState\n";
    return true;
}

void SinglePlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

void SinglePlayerMenuState::SpMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}
