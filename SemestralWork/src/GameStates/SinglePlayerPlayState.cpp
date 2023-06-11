#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/CollisionManager.hpp"
#include "../Levels/LevelParser.hpp"
#include "../GameObjects/Enemy.hpp"
#include "SinglePlayerPlayState.hpp"
#include "SinglePlayerLostState.hpp"
#include "SinglePlayerWonState.hpp"
#include "PauseMenuState.hpp"

/**
 * This method updates the current level as well as checks for a game pause
 */
void SinglePlayerPlayState::update()
{
    mLevel->update();
    updatePlayer();

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
    handleGameInformation();
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
    mScore = 0;

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

    std::cout << "Entering SinglePLayerPlayState." << std::endl;
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

    std::cout << "Exiting SinglePlayerPlayState." << std::endl;
    return true;
}

void SinglePlayerPlayState::updatePlayer()
{
    for (GameObject *obj: *mObjectLayer->getGameObjects())
    {
        if (Player1* player1 = dynamic_cast<Player1 *>(obj))
        {
            mLives = player1->getLives();
            mSpeed = player1->getSpeed();
            mRadius = player1->getRadius();
            mBombTime = player1->fastBomb();
            mImmortal = player1->isImmortal();
        }

        if(Enemy* enemy = dynamic_cast<Enemy *>(obj))
            if(TheCollisionManager::Instance()->isEnemyHit(enemy->getPosition()))
            {
                mNoOfEnemies--;
                mScore += 10;
            }
    }
}

void SinglePlayerPlayState::handleGameInformation()
{
    SDL_Color white = {255, 255, 255};
    TTF_Font* font = TheGame::Instance()->getFont();
    TTF_SetFontSize(font, 35);

    std::string p1 = TheGame::Instance()->getP1();
    std::string p1Lives = "Lives: " + std::to_string(mLives);
    std::string p1Speed = "Speed: " + std::to_string(mSpeed);
    std::string p1Radius = "Radius: " + std::to_string(mRadius);
    std::string p1Score = "Score: " + std::to_string(mScore);
    std::string p1Immortal = "Immortal";
    std::string p1FastBomb = "Explosion";

    if(!p1.empty())
        TheTextureManager::Instance()->drawText(p1, 10, 5, white, TheGame::Instance()->getRenderer(), font);
    else
        TheTextureManager::Instance()->drawText("Player1", 10, 5, white, TheGame::Instance()->getRenderer(), font);
    TheTextureManager::Instance()->drawText(p1Score, 150, 5, white, TheGame::Instance()->getRenderer(), font);

    TTF_SetFontSize(font, 30);
    TheTextureManager::Instance()->drawText(p1Lives, 10, 45, white, TheGame::Instance()->getRenderer(), font);
    TheTextureManager::Instance()->drawText(p1Speed, 10, 80, white, TheGame::Instance()->getRenderer(), font);
    TheTextureManager::Instance()->drawText(p1Radius, 150, 45, white, TheGame::Instance()->getRenderer(), font);

    if(mImmortal)
        TheTextureManager::Instance()->drawText(p1Immortal, 290, 45, white, TheGame::Instance()->getRenderer(),
                                                font);
    if(mBombTime)
        TheTextureManager::Instance()->drawText(p1FastBomb, 290, 80, white, TheGame::Instance()->getRenderer(),
                                                font);
}

std::string SinglePlayerPlayState::getStateID() const
{
    return mStateID;
}

const std::string SinglePlayerPlayState::mStateID = "SINGLE_PLAYER_PLAY_STATE";
