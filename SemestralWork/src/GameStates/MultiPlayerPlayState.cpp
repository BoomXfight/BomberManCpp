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
#include <fstream>
#include <sstream>
#include <algorithm>

struct PlayerScore
{
    std::string name;
    int score;
};

bool comparePlayers(const PlayerScore& p1, const PlayerScore& p2)
{
    return p1.score > p2.score;
}

/**
 * This method updates the current level as well as checks for a game pause
 */
void MultiPlayerPlayState::update()
{
    mLevel->update();
    mNow = SDL_GetTicks();

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
            }

            else if (Player2* player2 = dynamic_cast<Player2 *>(obj))
            {
                mP2Lives = player2->getLives();
                mP2Dmg = player2->isDamaged();
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
    mP1Score = 0;
    mP2Score = 0;
    mP1Dmg = false;
    mP2Dmg = false;
    mNow = SDL_GetTicks();
    mDmg1Timer = SDL_GetTicks();
    mDmg2Timer = SDL_GetTicks();
    std::cout << "Entering MultiPLayerPlayState" << std::endl;
    return true;
}

/**
 * This method cleans up after the current game state
 * @return true
 */
bool MultiPlayerPlayState::onExit()
{
    std::string p1 = TheGame::Instance()->getP1();
    std::string p2 = TheGame::Instance()->getP2();
    if(!p1.empty() || !p2.empty())
    {
        std::ifstream fileIn("../src/ScoreBoard.txt");
        if (!fileIn)
            std::cout << "Failed to open the score file." << std::endl;

        std::vector<PlayerScore> players;
        std::string line;

        // Load from file
        while(getline(fileIn, line))
        {
            std::string name;
            int score;
            std::istringstream iss(line);
            if(iss >> name >> score)
                players.push_back({name,score});
        }
        fileIn.close();

        bool p1set = false;
        bool p2set = false;

        // Modify based on the results
        for(auto it = players.begin(); it != players.end(); it++)
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
            players.push_back({p1, mP1Score});
        if(!p2set && !p2.empty())
            players.push_back({p2, mP2Score});

        // Sort the vector
        std::sort(players.begin(), players.end(), comparePlayers);

        // Write to the file
        std::ofstream fileOut("../src/ScoreBoard.txt");
        if (!fileOut)
            std::cout << "Failed to open the scores file for writing." << std::endl;

        for (const auto& player : players) {
            fileOut << player.name << " " << player.score << std::endl;
        }

        fileOut.close();
    }

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
