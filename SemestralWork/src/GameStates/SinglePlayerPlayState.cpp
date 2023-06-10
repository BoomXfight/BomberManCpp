#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/CollisionManager.hpp"
#include "../Levels/LevelParser.hpp"
#include "../Levels/ObjectLayer.hpp"
#include "../GameObjects/Player1.hpp"
#include "../GameObjects/Enemy.hpp"
#include "SinglePlayerPlayState.hpp"
#include "SinglePlayerLostState.hpp"
#include "SinglePlayerWonState.hpp"
#include "PauseMenuState.hpp"
#include <iostream>

/**
 * This method updates the current level as well as checks for a game pause
 */
void SinglePlayerPlayState::update()
{
    mLevel->update();

    for (GameObject *obj: *mObjectLayer->getGameObjects())
    {
        if (Player1* player1 = dynamic_cast<Player1 *>(obj))
            mLives = player1->getLives();
    }

    for (GameObject *obj: *mObjectLayer->getGameObjects())
    {
        if(Enemy* enemy = dynamic_cast<Enemy *>(obj))
            if(TheCollisionManager::Instance()->isEnemyHit(enemy->getPosition()))
            {
                mNoOfEnemies--;
                mPoints += 10;
            }
    }

    if(mLives == 0)
        TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerLostState);
    if(mNoOfEnemies == 0)
        TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerWonState);

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


    mNoOfEnemies = 0;
    for (Layer* layer : *mLevel->getLayers())
    {
        if (ObjectLayer* objLayer = dynamic_cast<ObjectLayer*>(layer))
        {
            mObjectLayer = objLayer;
            break;
        }
    }

    if (mObjectLayer != nullptr)
    {
        for (GameObject *obj: *mObjectLayer->getGameObjects())
        {
            if (Enemy* enemy = dynamic_cast<Enemy *>(obj))
                mNoOfEnemies ++;
        }
    }

    std::cout << mNoOfEnemies << std::endl;
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
