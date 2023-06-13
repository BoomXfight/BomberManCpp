#include "InputHandler.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "CollisionManager.hpp"
#include "LevelParser.hpp"
#include "Enemy.hpp"
#include "SinglePlayerPlayState.hpp"
#include "SinglePlayerLostState.hpp"
#include "SinglePlayerWonState.hpp"
#include "PauseMenuState.hpp"
#include <algorithm>

SinglePlayerPlayState::SinglePlayerPlayState() : mLives(0), mSpeed(0), mRadius(0), mNoOfEnemies(0), mScore(0), 
					         mBombTime(false), mImmortal(false)
{}

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

void SinglePlayerPlayState::render()
{
    mLevel->render();
    renderGameInformation();
}

bool SinglePlayerPlayState::onEnter()
{
    try
    {
        LevelParser levelParser;
        mLevel = levelParser.parseLevel("examples/map1.tmx");
        if (mLevel == nullptr)
            throw std::runtime_error("Failed to load the Level file.");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    mLives = 0;
    mSpeed = 0;
    mRadius = 0;
    mNoOfEnemies = 0;
    mScore = 0;
    mBombTime = false;
    mImmortal = false;
    
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
            if (dynamic_cast<Enemy *>(obj))
                mNoOfEnemies ++;
        }
    }

    std::cout << "Entering SinglePLayerPlayState." << std::endl;
    return true;
}

bool SinglePlayerPlayState::onExit()
{
    if(!TheGame::Instance()->getP1().empty())
    {
        std::vector<PlayerScore> players;

        loadPlayerScores("examples/Scoreboard.txt", players);
        updatePlayersScore(players);
        std::sort(players.begin(), players.end(), comparePlayers);
        modifyPlayerScores("examples/Scoreboard.txt", players);
    }

    for(size_t i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(size_t i = 0; i < mTextureIDList.size(); i++)
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

void SinglePlayerPlayState::renderGameInformation() const
{
    SDL_Color white = {255, 255, 255};
    TTF_Font* font1 = TheGame::Instance()->getFont1();
    TTF_Font* font2 = TheGame::Instance()->getFont2();

    std::string p1 = TheGame::Instance()->getP1();
    std::string p1Lives = "Lives: " + std::to_string(mLives);
    std::string p1Speed = "Speed: " + std::to_string(mSpeed);
    std::string p1Radius = "Radius: " + std::to_string(mRadius);
    std::string p1Score = "Score: " + std::to_string(mScore);
    std::string p1Immortal = "Immortal";
    std::string p1FastBomb = "Explosion";

    if(!p1.empty())
        TheTextureManager::Instance()->drawText(p1, 10, 5, white, TheGame::Instance()->getRenderer(), font1);
    else
        TheTextureManager::Instance()->drawText("Player1", 10, 5, white, TheGame::Instance()->getRenderer(), font1);
    TheTextureManager::Instance()->drawText(p1Score, 150, 5, white, TheGame::Instance()->getRenderer(), font1);

    TheTextureManager::Instance()->drawText(p1Lives, 10, 45, white, TheGame::Instance()->getRenderer(), font2);
    TheTextureManager::Instance()->drawText(p1Speed, 10, 80, white, TheGame::Instance()->getRenderer(), font2);
    TheTextureManager::Instance()->drawText(p1Radius, 150, 45, white, TheGame::Instance()->getRenderer(), font2);

    if(mImmortal)
        TheTextureManager::Instance()->drawText(p1Immortal, 290, 45, white, TheGame::Instance()->getRenderer(),
                                                font2);
    if(mBombTime)
        TheTextureManager::Instance()->drawText(p1FastBomb, 290, 80, white, TheGame::Instance()->getRenderer(),
                                                font2);
}

void SinglePlayerPlayState::updatePlayersScore(std::vector<PlayerScore>& pScores)
{
    std::string p1 = TheGame::Instance()->getP1();
    bool p1set = false;

    // Modify based on the results
    for(auto it = pScores.begin(); it != pScores.end(); it++)
    {
        if(it->name == p1) {
            it->score += mScore;
            p1set = true;
        }
    }

    if(!p1set && !p1.empty())
        pScores.push_back({p1, mScore});
}

std::string SinglePlayerPlayState::getStateID() const
{
    return mStateID;
}

const std::string SinglePlayerPlayState::mStateID = "SINGLE_PLAYER_PLAY_STATE";
