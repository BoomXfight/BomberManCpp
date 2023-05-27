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
    || !TheTextureManager::Instance()->load("../Assets/Back.png", "Back", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Bomber2.png", "Bomber", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Nickname.png", "Nickname", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/PlayButton.png", "Play", TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load the button :" << SDL_GetError() << "\n";
        return false;
    }

    GameObject* singlePlayer = new StaticObject(new LoaderParams(150, 20, 660, 166, "SinglePlayer"));
    GameObject* bomber = new StaticObject(new LoaderParams(520, 220, 350, 304, "Bomber"));
    GameObject* nick = new StaticObject(new LoaderParams(150, 200, 180, 30, "Nickname"));
    GameObject* exit = new MenuButton(new LoaderParams(840, 40, 90, 50, "Exit"), menuToQuit);
    GameObject* back = new MenuButton(new LoaderParams(30, 40, 90, 50, "Back"), SpMenuToMainMenu);
    GameObject* play = new MenuButton(new LoaderParams(150, 330, 200, 160, "Play"), SpMenuToMainMenu);

    m_gameObjects.push_back(singlePlayer);
    m_gameObjects.push_back(bomber);
    m_gameObjects.push_back(nick);
    m_gameObjects.push_back(exit);
    m_gameObjects.push_back(back);
    m_gameObjects.push_back(play);

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
    TheTextureManager::Instance()->clearFromTextureMap("Back");
    TheTextureManager::Instance()->clearFromTextureMap("Bomber");
    TheTextureManager::Instance()->clearFromTextureMap("Nick");
    TheTextureManager::Instance()->clearFromTextureMap("Play");
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

void SinglePlayerMenuState::SpMenuToSpPlay()
{
    // if nickname set -> change to single player play state (the actual game)
}

