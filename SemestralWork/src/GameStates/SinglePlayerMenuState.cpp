#include "../Singletons/TextureManager.hpp"
#include "../Singletons/Game.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "SinglePlayerMenuState.hpp"
#include "MainMenuState.hpp"
#include "SinglePlayerPlayState.hpp"
#include "StateParser.hpp"

bool SinglePlayerMenuState::onEnter()
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

    mCallbacks.push_back(menuToQuit);
    mCallbacks.push_back(spMenuToMainMenu);
    mCallbacks.push_back(spMenuToSpPlay);

    setCallbacks(mCallbacks);
    std::cout << "Entering SinglePlayerMenuState." << std::endl;
    return true;
}

bool SinglePlayerMenuState::onExit()
{
    if(TextSquare* a = dynamic_cast<TextSquare*>(mGameObjects[0]))
    {
        TheGame::Instance()->setP1(a->getText());
        std::cout << "P1 set." << std::endl;
    }

    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting SinglePlayerMenuState." << std::endl;
    return true;
}

std::string SinglePlayerMenuState::getStateID() const
{
    return mStateID;
}

void SinglePlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

void SinglePlayerMenuState::spMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void SinglePlayerMenuState::spMenuToSpPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerPlayState);

    if(TheGame::Instance()->P1Ready())
        std::cout << "Playing as : " << TheGame::Instance()->getP1() << "." << std::endl;
    else
        std::cout << "Playing as : guest." << std::endl;
}

// a unique ID for SinglePlayerPlayState used in the xml file
const std::string SinglePlayerMenuState::mStateID = "SINGLE_PLAYER_MENU_STATE";
