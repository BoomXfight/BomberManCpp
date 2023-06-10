#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Levels/LevelParser.hpp"
#include "SinglePlayerPlayState.hpp"
#include "../GameStates/PauseMenuState.hpp"
#include <iostream>

/**
 * This method updates the current level as well as checks for a game pause
 */
void SinglePlayerPlayState::update()
{
    mLevel->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        TheGame::Instance()->getStateMachine()->pushState(new PauseMenuState());
}

/**
 * This method renders the current level
 */
void SinglePlayerPlayState::render()
{
    mLevel->render();
}

/**
 * This method initializes the current level from the file
 * @return true
 */
bool SinglePlayerPlayState::onEnter()
{
    LevelParser levelParser;
    mLevel = levelParser.parseLevel("../Assets/Maps/map1.tmx");
    std::cout << "Entering SinglePLayerPlayState" << std::endl;
    return true;
}

/**
 * This method cleans up after the current game state
 * @return true
 */
bool SinglePlayerPlayState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting SinglePlayerPlayState" << std::endl;
    return true;
}

std::string SinglePlayerPlayState::getStateID() const
{
    return mPlayID;
}

const std::string SinglePlayerPlayState::mPlayID = "SINGLE_PLAYER_PLAY_STATE";
