#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/CollisionManager.hpp"
#include "../Levels/LevelParser.hpp"
#include "MultiPlayerPlayState.hpp"
#include "../GameStates/GameState.hpp"
#include "../GameStates/PauseMenuState.hpp"
#include <iostream>

/**
 * This method updates the current level as well as checks for a game pause
 */
void MultiPlayerPlayState::update()
{
    mLevel->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        TheGame::Instance()->getStateMachine()->pushState(new PauseMenuState());
}

/**
 * This method renders the current level
 */
void MultiPlayerPlayState::render()
{
    mLevel->render();
}

/**
 * This method initializes the current level from the file
 * @return true
 */
bool MultiPlayerPlayState::onEnter()
{
    LevelParser levelParser;
    mLevel = levelParser.parseLevel("../Assets/Maps/map2.tmx");
    std::cout << "Entering MultiPLayerPlayState" << std::endl;
    return true;
}

/**
 * This method cleans up after the current game state
 * @return true
 */
bool MultiPlayerPlayState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting MinglePlayerPlayState" << std::endl;
    return true;
}

std::string MultiPlayerPlayState::getStateID() const
{
    return mPlayID;
}

const std::string MultiPlayerPlayState::mPlayID = "MULTI_PLAYER_PLAY_STATE";
