#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/CollisionManager.hpp"
#include "../Levels/LevelParser.hpp"
#include "../GameObjects/Player2.hpp"
#include "../GameStates/GameState.hpp"
#include "../GameStates/PauseMenuState.hpp"
#include "../GameStates/MainMenuState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "MultiPlayer1WinState.hpp"
#include "MultiPlayer2WinState.hpp"
#include <iostream>

/**
 * This method updates the current level as well as checks for a game pause
 */
void MultiPlayerPlayState::update()
{
    mLevel->update();

    ObjectLayer* objectLayer = nullptr;
    for (Layer* layer : *mLevel->getLayers())
    {
        if (ObjectLayer* objLayer = dynamic_cast<ObjectLayer*>(layer))
        {
            objectLayer = objLayer;
            break;
        }
    }

    if (objectLayer != nullptr)
    {
        for (GameObject *obj: *objectLayer->getGameObjects()) {
            if (Player1 *player1 = dynamic_cast<Player1 *>(obj))
                mP1Lives = player1->getLives();

            else if (Player2 *player2 = dynamic_cast<Player2 *>(obj))
                mP2Lives = player2->getLives();
        }
    }

    if(mP1Lives == 0)
        TheGame::Instance()->getStateMachine()->changeState(new MultiPlayer2WinState);
    else if(mP2Lives == 0)
        TheGame::Instance()->getStateMachine()->changeState(new MultiPlayer1WinState);

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
