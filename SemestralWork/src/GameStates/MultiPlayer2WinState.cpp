#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "MultiPlayer2WinState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"

bool MultiPlayer2WinState::onEnter()
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

    std::cout << "Entering MultiPlayer2WinState." << std::endl;
    return true;
}

bool MultiPlayer2WinState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "Exiting MultiPlayer2WinState." << std::endl;
    return true;
}

std::string MultiPlayer2WinState::getStateID() const
{
    return mStateID;
}

void MultiPlayer2WinState::playAgain()
{
    TheGame::Instance()->getStateMachine()->changeState(new (MultiPlayerPlayState));
}

void MultiPlayer2WinState::returnToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void MultiPlayer2WinState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string MultiPlayer2WinState::mStateID = "MULTI_PLAYER2_WIN_STATE";
