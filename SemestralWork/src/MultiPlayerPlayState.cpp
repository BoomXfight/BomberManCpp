#include "MultiPlayerPlayState.hpp"
#include "GameState.hpp"
#include <iostream>

const std::string MultiPlayerPlayState::s_menuID = "SinglePlayerPlay";

void MultiPlayerPlayState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

void MultiPlayerPlayState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

bool MultiPlayerPlayState::onEnter()
{
    std::cout << "Entering SinglePLayerPlayState" << std::endl;
}

bool MultiPlayerPlayState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    std::cout << "exiting SinglePlayerPlayState\n";
    return true;
}


