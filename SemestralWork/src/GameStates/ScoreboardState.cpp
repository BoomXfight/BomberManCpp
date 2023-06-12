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

void loadPlayerScores(const std::string& pFilename, std::vector<PlayerScore>& pPlayers)
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

void modifyPlayerScores(const std::string& pFilename, const std::vector<PlayerScore>& pPlayers)
{
    std::ofstream fileOut(pFilename);
    if (!fileOut)
        std::cout << "Failed to open the scores file for writing." << std::endl;

    for (const auto& it : pPlayers) {
        fileOut << it.name << " " << it.score << std::endl;
    }

    fileOut.close();
}

void ScoreboardState::render()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();

    int cnt = 1;
    for(auto it = mPlayers.begin(); it != mPlayers.end(); it++)
    {
        SDL_Color textColor = {255, 255, 255};
        TTF_Font* font = TheGame::Instance()->getFont();
        TTF_SetFontSize(font,50);
        std::string playerInfo = std::to_string(cnt) + ". " + it->name + " " + std::to_string(it->score);
        TheTextureManager::Instance()->drawText(playerInfo, 200, 105 + cnt * 55, textColor,
                                                TheGame::Instance()->getRenderer(), font);
        cnt ++;
        if(cnt == 6)
            break;
    }
}

bool ScoreboardState::onEnter()
{
    try
    {
        StateParser stateParser;
        if (!stateParser.parseState("../Assets/GameStates.xml", mMenuID, &mGameObjects,
                                    &mTextureIDList))
            throw std::runtime_error("Failed to load GameStates load file.");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    mCallbacks.push_back(exit);
    mCallbacks.push_back(scoreboardToMainMenu);
    setCallbacks(mCallbacks);
    loadPlayerScores("../Assets/Scoreboard.txt", mPlayers);

    std::cout << "Entering ScoreboardState." << std::endl;
    return true;
}

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
