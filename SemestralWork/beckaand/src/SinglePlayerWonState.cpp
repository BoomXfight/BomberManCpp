#include "Game.hpp"
#include "TextureManager.hpp"
#include "InputHandler.hpp"
#include "SinglePlayerWonState.hpp"
#include "SinglePlayerPlayState.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"


/**
 * This method initializes the SinglePlayerWonState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool SinglePlayerWonState::onEnter()
{
    try
    {
        StateParser stateParser;
        if (!stateParser.parseState("examples/GameStates.xml", mStateID, &mGameObjects,
                                    &mTextureIDList))
            throw std::runtime_error("Failed to load GameStates load file.");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    mCallbacks.push_back(playAgain);
    mCallbacks.push_back(returnToMainMenu);
    mCallbacks.push_back(exit);
    setCallbacks(mCallbacks);

    std::cout << "Entering SinglePlayerWonState." << std::endl;
    return true;
}

/**
 * This method cleans up at the end of SinglePlayerWonState
 * @return true
 */
bool SinglePlayerWonState::onExit()
{
    for(size_t i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(size_t i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "Exiting SinglePlayerWonState." << std::endl;
    return true;
}

std::string SinglePlayerWonState::getStateID() const
{
    return mStateID;
}

void SinglePlayerWonState::playAgain()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerPlayState());
}

void SinglePlayerWonState::returnToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void SinglePlayerWonState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string SinglePlayerWonState::mStateID = "SINGLE_PLAYER_WON_STATE";
