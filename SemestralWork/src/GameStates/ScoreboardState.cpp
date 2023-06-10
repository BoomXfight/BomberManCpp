#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../Singletons/Game.hpp"
#include "../GameObjects/MenuButton.hpp"
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
 * This method updates the gameObjects of the ScoreboardState
 */
void ScoreboardState::update()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->update();
}

/**
 * This method renders the gameObjects of the ScoreboardState
 */
void ScoreboardState::render()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();

    int cnt = 1;
    int x = 200;
    int y = 105;
    for(auto it = mPlayers.begin(); it != mPlayers.end(); it++)
    {
        SDL_Color textColor = {255, 255, 255};
        std::string playerInfo = std::to_string(cnt) + ". " + it->name + " " + std::to_string(it->score);
        TheTextureManager::Instance()->drawText(playerInfo, x, y + cnt * 55, textColor,
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

    mCallbacks.push_back(nullptr);
    mCallbacks.push_back(exit);
    mCallbacks.push_back(scoreboardToMainMenu);
    setCallbacks(mCallbacks);

    // getting the players
    std::ifstream fileIn("../src/ScoreBoard.txt");
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
            mPlayers.push_back({name,score});
    }
    fileIn.close();

    std::cout << "Entering ScoreboardState" << std::endl;
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

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "Exiting ScoreboardState" << std::endl;
    return true;
}

std::string ScoreboardState::getStateID() const
{
    return mMenuID;
}

/**
 * This method assigns a callback function to gameObjects that require it
 * @param pCallbacks
 */
void ScoreboardState::setCallbacks(const std::vector<Callback> &pCallbacks)
{
    for(int i = 0; i < mGameObjects.size(); i++)
    {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(mGameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(mGameObjects[i]);
            pButton->setCallback(pCallbacks[pButton->getCallbackID()]);
        }
    }
}

/**
 * Callback function that switches to MainMenuState
 */
void ScoreboardState::scoreboardToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

/**
 * Callback function that ends the game
 */
void ScoreboardState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string ScoreboardState::mMenuID = "SCOREBOARD_MENU_STATE";
