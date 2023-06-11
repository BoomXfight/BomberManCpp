#include "../Singletons/TextureManager.hpp"
#include "../Singletons/Game.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"
#include "SinglePlayerMenuState.hpp"
#include "MultiPlayerMenuState.hpp"
#include "ScoreboardState.hpp"

bool MainMenuState::onEnter()
{
    try
    {
        StateParser stateParser;
        if (!stateParser.parseState("../src/GameStates.xml", mStateID, &mGameObjects,
                                    &mTextureIDList))
            throw std::runtime_error("Failed to load GameStates load file.");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    // Initialize the callback functions
    mCallbacks.push_back(menuToSinglePlayer);
    mCallbacks.push_back(menuToMultiPlayer);
    mCallbacks.push_back(menuToScoreboard);
    mCallbacks.push_back(menuToQuit);

    setCallbacks(mCallbacks);
    std::cout << "Entering MainMenuState." << std::endl;
    return true;
}

bool MainMenuState::onExit()
{
    TheGame ::Instance()->setP1(""); // Reset the player names
    TheGame ::Instance()->setP2("");

    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting MainMenuState." << std::endl;
    return true;
}

std::string MainMenuState::getStateID() const
{
    return mStateID;
}

void MainMenuState::menuToSinglePlayer()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerMenuState());
}

void MainMenuState::menuToMultiPlayer()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerMenuState());
};

void MainMenuState::menuToScoreboard()
{
    TheGame::Instance()->getStateMachine()->changeState(new ScoreboardState);
}

void MainMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

// a unique ID for the MainMenuState used in the xml load file
const std::string MainMenuState::mStateID = "MAIN_MENU_STATE";
