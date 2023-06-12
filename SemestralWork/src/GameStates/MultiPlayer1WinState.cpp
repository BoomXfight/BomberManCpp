#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "MultiPlayer1WinState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"

bool MultiPlayer1WinState::onEnter()
{
    try
    {
        StateParser stateParser;
        if (!stateParser.parseState("../Assets/GameStates.xml", mStateID, &mGameObjects,
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

    std::cout << "Entering MultiPlayer1WinState." << std::endl;
    return true;
}

bool MultiPlayer1WinState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "Exiting MultiPlayer1WinState." << std::endl;
    return true;
}

std::string MultiPlayer1WinState::getStateID() const
{
    return mStateID;
}

void MultiPlayer1WinState::playAgain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerPlayState());
}

void MultiPlayer1WinState::returnToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void MultiPlayer1WinState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string MultiPlayer1WinState::mStateID = "MULTI_PLAYER1_WIN_STATE";
