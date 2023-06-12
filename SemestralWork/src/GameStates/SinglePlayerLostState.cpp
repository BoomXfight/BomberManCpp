#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "SinglePlayerLostState.hpp"
#include "SinglePlayerPlayState.hpp"
#include "MainMenuState.hpp"
#include "StateParser.hpp"

bool SinglePlayerLostState::onEnter()
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
    std::cout << "Entering SinglePlayerLostState." << std::endl;
    return true;
}

bool SinglePlayerLostState::onExit()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "SinglePlayerLostState." << std::endl;
    return true;
}

std::string SinglePlayerLostState::getStateID() const
{
    return mStateID;
}

void SinglePlayerLostState::playAgain()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerPlayState());
}

void SinglePlayerLostState::returnToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void SinglePlayerLostState::exit()
{
    TheGame::Instance()->quit();
}

// a unique ID for this state used in the xml file
const std::string SinglePlayerLostState::mStateID = "SINGLE_PLAYER_LOST_STATE";
