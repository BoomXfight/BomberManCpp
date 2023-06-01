#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../StateParser.hpp"
#include "SinglePlayerPlayState.hpp"
#include "GameState.hpp"
#include "PauseMenuState.hpp"
#include <iostream>

const std::string SinglePlayerPlayState::s_menuID = "SINGLE_PLAYER_PLAY_STATE";

void SinglePlayerPlayState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseMenuState());
    }
}

void SinglePlayerPlayState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

bool SinglePlayerPlayState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("../src/GameStates.xml", s_menuID, &m_gameObjects,&m_textureIDList);
    std::cout << "Entering SinglePLayerPlayState" << std::endl;
}

bool SinglePlayerPlayState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    std::cout << "exiting SinglePlayerPlayState\n";
    return true;
}

