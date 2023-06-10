#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "MainMenuState.hpp"
#include "ScoreboardState.hpp"
#include "StateParser.hpp"
#include <fstream>
#include <sstream>

bool comparePlayers(const PlayerScore& p1, const PlayerScore& p2)
{
    return p1.score > p2.score;
}

/**
 * This function loads the score board into the program
 * @param[in] pFilename
 * @param[in,out] pPlayers
 */
void loadPlayers(const std::string& pFilename, std::vector<PlayerScore>& pPlayers)
{
    std::ifstream fileIn(pFilename);
    if (!fileIn)
        std::cout << "Failed to open the score file." << std::endl;

    std::string line;

    // Load from file
    while(getline(fileIn, line))
    {
        std::string name;
        int score;
        std::istringstream iss(line);
        if(iss >> name >> score)
            pPlayers.push_back({name,score});
    }
    fileIn.close();
}

/**
 * This method renders the gameObjects of the ScoreboardState
 */
void ScoreboardState::render()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();

    int cnt = 1;
    for(auto it = mPlayers.begin(); it != mPlayers.end(); it++)
    {
        SDL_Color textColor = {255, 255, 255};
        std::string playerInfo = std::to_string(cnt) + ". " + it->name + " " + std::to_string(it->score);
        TheTextureManager::Instance()->drawText(playerInfo, 200, 105 + cnt * 55, textColor,
                                                TheGame::Instance()->getRenderer());
        cnt ++;
        if(cnt == 6)
            break;
    }
}

/**
 * This method initializes the ScoreboardState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool ScoreboardState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mMenuID, &mGameObjects,&mTextureIDList))
        return false;

    mCallbacks.push_back(exit);
    mCallbacks.push_back(scoreboardToMainMenu);
    setCallbacks(mCallbacks);
    loadPlayers("../src/Scoreboard.txt", mPlayers);

    std::cout << "Entering ScoreboardState." << std::endl;
    return true;
}

/**
 * This method cleans up at the end of ScoreboardState
 * @return true
 */
bool ScoreboardState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    TheInputHandler::Instance()->reset();
    std::cout << "Exiting ScoreboardState." << std::endl;
    return true;
}

std::string ScoreboardState::getStateID() const
{
    return mMenuID;
}

void ScoreboardState::scoreboardToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void ScoreboardState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string ScoreboardState::mMenuID = "SCOREBOARD_MENU_STATE";
