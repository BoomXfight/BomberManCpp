#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/CollisionManager.hpp"
#include "../Levels/LevelParser.hpp"
#include "../GameObjects/Player2.hpp"
#include "../GameStates/PauseMenuState.hpp"
#include "../GameStates/MainMenuState.hpp"
#include "ScoreboardState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "MultiPlayer1WinState.hpp"
#include "MultiPlayer2WinState.hpp"
#include <iostream>
#include <algorithm>

/**
 * This method updates the current level as well as checks for a game pause
 */
void MultiPlayerPlayState::update()
{
    mLevel->update();
    mNow = SDL_GetTicks();
    handlePlayers();

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
    handlePlayer1Information();
    handlePlayer2Information();
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
    mP1Score = 0;
    mP2Score = 0;
    mP1Lives = 3;
    mP2Lives = 3;
    mP1Radius = 2;
    mP2Radius = 2;
    mP1Speed = 4;
    mP2Speed = 4;
    mP1BombTime = false;
    mP2BombTime = false;
    mP1Immortal = false;
    mP2Immortal = false;
    mP1Dmg = false;
    mP2Dmg = false;
    mNow = SDL_GetTicks();
    mDmg1Timer = SDL_GetTicks();
    mDmg2Timer = SDL_GetTicks();
    std::cout << "Entering MultiPLayerPlayState." << std::endl;
    return true;
}

/**
 * This method cleans up after the current game state and saves the result scores
 * @return true
 */
bool MultiPlayerPlayState::onExit()
{
    //Update scores;
    if(!TheGame::Instance()->getP1().empty() || !TheGame::Instance()->getP2().empty())
    {
        std::vector<PlayerScore> players;

        loadPlayerScores("../src/Scoreboard.txt", players);
        updatePlayersScore(players);
        std::sort(players.begin(), players.end(), comparePlayers);
        modifyPlayerScores("../src/Scoreboard.txt", players);
    }

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting MinglePlayerPlayState." << std::endl;
    return true;
}

std::string MultiPlayerPlayState::getStateID() const
{
    return mStateID;
}

/**
 * This method gets the necessary player information
 */
void MultiPlayerPlayState::handlePlayers()
{
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
        for (GameObject *obj: *objectLayer->getGameObjects())
        {
            if (Player1* player1 = dynamic_cast<Player1 *>(obj))
            {
                mP1Lives = player1->getLives();
                mP1Dmg = player1->isDamaged();
                mP1Speed = player1->getSpeed();
                mP1Radius = player1->getRadius();
                mP1Immortal = player1->isImmortal();
                mP1BombTime = player1->fastBomb();
            }

            else if (Player2* player2 = dynamic_cast<Player2 *>(obj))
            {
                mP2Lives = player2->getLives();
                mP2Dmg = player2->isDamaged();
                mP2Speed = player2->getSpeed();
                mP2Radius = player2->getRadius();
                mP2Immortal = player2->isImmortal();
                mP2BombTime = player2->fastBomb();
            }
        }
    }

    if(mP1Dmg && ((mNow - mDmg1Timer) / 1000 > 3))
    {
        mDmg1Timer = SDL_GetTicks();
        mP1Dmg = false;
        mP2Score += 20;
        std::cout << "S2:" << mP2Score << std::endl;
    }

    if(mP2Dmg && ((mNow - mDmg2Timer) / 1000 > 3))
    {
        mDmg2Timer = SDL_GetTicks();
        mP1Score += 20;
        mP2Dmg = false;
        std::cout << "S1:" << mP1Score << std::endl;
    }
}

/**
 * This method handles the rendering of player1 information to the screen
 */
void MultiPlayerPlayState::handlePlayer1Information() const
{
    SDL_Color white = {255, 255, 255};
    TTF_Font* font = TheGame::Instance()->getFont();
    TTF_SetFontSize(font, 35);

    std::string p1 = TheGame::Instance()->getP1();
    std::string p1Lives = "Lives: " + std::to_string(mP1Lives);
    std::string p1Speed = "Speed: " + std::to_string(mP1Speed);
    std::string p1Radius = "Radius: " + std::to_string(mP1Radius);
    std::string p1Score = "Score: " + std::to_string(mP1Score);
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

    if(mP1Immortal)
        TheTextureManager::Instance()->drawText(p1Immortal, 290, 45, white, TheGame::Instance()->getRenderer(),
                                                font);
    if(mP1BombTime)
        TheTextureManager::Instance()->drawText(p1FastBomb, 290, 80, white, TheGame::Instance()->getRenderer(),
                                                font);
}

/**
 * This method handles the rendering of player2 information to the screen
 */
void MultiPlayerPlayState::handlePlayer2Information() const
{
    SDL_Color white = {255, 255, 255};
    TTF_Font* font = TheGame::Instance()->getFont();
    TTF_SetFontSize(font, 35);

    std::string p2 = TheGame::Instance()->getP2();
    std::string p2Lives = "Lives: " + std::to_string(mP2Lives);
    std::string p2Speed = "Speed: " + std::to_string(mP2Speed);
    std::string p2Radius = "Radius: " + std::to_string(mP2Radius);
    std::string p2Score = "Score: " + std::to_string(mP2Score);
    std::string p2Immortal = "Immortal";
    std::string p2FastBomb = "Explosion";

    if(!p2.empty())
        TheTextureManager::Instance()->drawText(p2, 500, 5, white, TheGame::Instance()->getRenderer(), font);
    else
        TheTextureManager::Instance()->drawText("Player2", 500, 5, white, TheGame::Instance()->getRenderer(), font);
    TheTextureManager::Instance()->drawText(p2Score, 650, 5, white, TheGame::Instance()->getRenderer(), font);

    TTF_SetFontSize(font, 30);
    TheTextureManager::Instance()->drawText(p2Lives, 500, 45, white, TheGame::Instance()->getRenderer(), font);
    TheTextureManager::Instance()->drawText(p2Speed, 500, 80, white, TheGame::Instance()->getRenderer(), font);
    TheTextureManager::Instance()->drawText(p2Radius, 650, 45, white, TheGame::Instance()->getRenderer(), font);

    if(mP2Immortal)
        TheTextureManager::Instance()->drawText(p2Immortal, 790, 45, white,TheGame::Instance()->getRenderer(),font);
    if(mP2BombTime)
        TheTextureManager::Instance()->drawText(p2FastBomb, 790, 80, white,TheGame::Instance()->getRenderer(),font);
}

/**
 * This method updates the player scores at the end of the game
 * @param[in,out] pScores
 */
void MultiPlayerPlayState::updatePlayersScore(std::vector<PlayerScore>& pScores)
{
    std::string p1 = TheGame::Instance()->getP1();
    std::string p2 = TheGame::Instance()->getP2();
    bool p1set = false;
    bool p2set = false;

    // Modify based on the results
    for(auto it = pScores.begin(); it != pScores.end(); it++)
    {
        if(it->name == p1) {
            it->score += mP1Score;
            p1set = true;
        }

        else if(it->name == p2) {
            it->score += mP2Score;
            p2set = true;
        }
    }

    if(!p1set && !p1.empty())
        pScores.push_back({p1, mP1Score});
    if(!p2set && !p2.empty())
        pScores.push_back({p2, mP2Score});
}

const std::string MultiPlayerPlayState::mStateID = "MULTI_PLAYER_PLAY_STATE";
