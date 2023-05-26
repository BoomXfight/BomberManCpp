#include "PlayState.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void PlayState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter()
{
    if(!TheTextureManager::Instance()->load("../Assets/Helicopter.png", "helicopter", TheGame::Instance()->getRenderer()))
    {
        return false;
    }
    GameObject* player = new Player(new LoaderParams(0, 0, 131,80, "helicopter"));
    m_gameObjects.push_back(player);
    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("helicopter");
    std::cout << "exiting PlayState\n";
    return true;
}