#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "SinglePlayerPlayState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include <iostream>

const std::string SinglePlayerPlayState::s_menuID = "SinglePlayerPlay";

void SinglePlayerPlayState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
}

void SinglePlayerPlayState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

bool SinglePlayerPlayState::onEnter()
{
    std::cout << "Entering SinglePLayerPlayState" << std::endl;
}

bool SinglePlayerPlayState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    std::cout << "exiting SinglePlayerPlayState\n";
    return true;
}


