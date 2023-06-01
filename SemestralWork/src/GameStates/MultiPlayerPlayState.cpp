#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Levels/LevelParser.hpp"
#include "MultiPlayerPlayState.hpp"
#include "GameState.hpp"
#include "PauseMenuState.hpp"
#include <iostream>

const std::string MultiPlayerPlayState::s_playID = "MULTI_PLAYER_PLAY_STATE";

/**
 * This method updates the current level as well as checks for a game pause
 */
void MultiPlayerPlayState::update()
{
    pLevel->update();
    pLevel->getLayers();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        TheGame::Instance()->getStateMachine()->pushState(new PauseMenuState());
}

/**
 * This method renders a current level
 */
void MultiPlayerPlayState::render()
{
    pLevel->render();
}

/**
 * This method initializes the current level from the file
 * @return true
 */
bool MultiPlayerPlayState::onEnter()
{
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("../Assets/Maps/map2.tmx");
    std::cout << "Entering MultiPLayerPlayState" << std::endl;
    return true;
}

/**
 * This method cleans up after the current game state
 * @return
 */
bool MultiPlayerPlayState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->clean();

    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);

    std::cout << "exiting SinglePlayerPlayState\n";
    return true;
}

std::string MultiPlayerPlayState::getStateID() const
{
    return s_playID;
}
