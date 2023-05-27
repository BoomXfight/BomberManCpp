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
    || !TheTextureManager::Instance()->load("../Assets/Back.png", "Back", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Bomberman3.png", "BomberMan", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/BomberWoman.png", "BomberWoman", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Player1.png", "Player1", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/Player2.png", "Player2", TheGame::Instance()->getRenderer())
    || !TheTextureManager::Instance()->load("../Assets/PlayButton.png", "Play", TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load the button :" << SDL_GetError() << "\n";
        return false;
    }

    GameObject* multiPlayer = new StaticObject(new LoaderParams(150, 20, 660, 166, "MultiPlayer"));
    GameObject* bomberMan = new StaticObject(new LoaderParams(30, 220, 271, 300, "BomberMan"));
    GameObject* bomberWoman = new StaticObject(new LoaderParams(700, 220, 197, 300, "BomberWoman"));
    GameObject* player1 = new StaticObject(new LoaderParams(400, 200, 160, 30, "Player1"));
    GameObject* player2 = new StaticObject(new LoaderParams(400, 280, 160, 30, "Player2"));
    GameObject* exit = new MenuButton(new LoaderParams(840, 40, 90, 50, "Exit"), menuToQuit);
    GameObject* back = new MenuButton(new LoaderParams(30, 40, 90, 50, "Back"), SpMenuToMainMenu);
    GameObject* play = new MenuButton(new LoaderParams(380, 360, 200, 160, "Play"), SpMenuToMainMenu);

    m_gameObjects.push_back(multiPlayer);
    m_gameObjects.push_back(exit);
    m_gameObjects.push_back(back);
    m_gameObjects.push_back(bomberMan);
    m_gameObjects.push_back(bomberWoman);
    m_gameObjects.push_back(player1);
    m_gameObjects.push_back(player2);
    m_gameObjects.push_back(play);

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
