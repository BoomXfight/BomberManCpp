#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../StateParser.hpp"
#include "../LevelParser.hpp"
#include "MultiPlayerPlayState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include <iostream>

const std::string MultiPlayerPlayState::s_menuID = "MULTI_PLAYER_PLAY_STATE";

void MultiPlayerPlayState::update()
{
    pLevel->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
}

void MultiPlayerPlayState::render()
{
    pLevel->render();
}

bool MultiPlayerPlayState::onEnter()
{
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("../Assets/map1.tmx");
    std::cout << "Entering MultiPLayerPlayState" << std::endl;
    return true;
}

bool MultiPlayerPlayState::onExit()
{
    /*
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
     */
    std::cout << "exiting SinglePlayerPlayState\n";
    return true;
}


