#include "Game.hpp"
#include "TextureManager.hpp"
#include "InputHandler.hpp"
#include "PauseMenuState.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"

/**
 * This method initializes the PauseMenuState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool PauseMenuState::onEnter()
{
    try
    {
        StateParser stateParser;
        if (!stateParser.parseState("examples/GameStates.xml", mPauseID, &mGameObjects,
                                    &mTextureIDList))
            throw std::runtime_error("Failed to load GameStates load file.");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    mCallbacks.push_back(resumePlay);
    mCallbacks.push_back(pauseToMainMenu);
    mCallbacks.push_back(exit);

    setCallbacks(mCallbacks);
    std::cout << "Entering PauseMenuState." << std::endl;
    return true;
}

/**
 * This method cleans up at the end of PauseMenuState
 * @return true
 */
bool PauseMenuState::onExit()
{
    for(size_t i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(size_t i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    TheInputHandler::Instance()->reset();
    std::cout << "Exiting PauseMenuState." << std::endl;
    return true;
}

std::string PauseMenuState::getStateID() const
{
    return mPauseID;
}

void PauseMenuState::pauseToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseMenuState::resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}

void PauseMenuState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string PauseMenuState::mPauseID = "PAUSE_MENU_STATE";
