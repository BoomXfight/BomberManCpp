#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "MultiPlayerMenuState.hpp"
#include "MainMenuState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "StateParser.hpp"

bool MultiPlayerMenuState::onEnter()
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

    mCallbacks.push_back(menuToQuit);
    mCallbacks.push_back(mpMenuToMainMenu);
    mCallbacks.push_back(mpMenuToMpPlay);

    setCallbacks(mCallbacks);
    std::cout << "Entering MultiPlayerMenu state." << std::endl;
    return true;
}

bool MultiPlayerMenuState::onExit()
{
    if(TextSquare* a = dynamic_cast<TextSquare*>(mGameObjects[0]))
    {
        TheGame::Instance()->setP1(a->getText());
        std::cout << "P1 set." << std::endl;
    }

    if(TextSquare* b = dynamic_cast<TextSquare*>(mGameObjects[1]))
    {
        TheGame::Instance()->setP2(b->getText());
        std::cout << "P2 set." << std::endl;
    }

    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting MultiPlayerMenuState." << std::endl;
    return true;
}

std::string MultiPlayerMenuState::getStateID() const
{
    return mStateID;
}

void MultiPlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

void MultiPlayerMenuState::mpMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void MultiPlayerMenuState::mpMenuToMpPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerPlayState);

    if(TheGame::Instance()->P1Ready())
        std::cout << "Player1 : " << TheGame::Instance()->getP1() << "." << std::endl;
    else
        std::cout << "Player1 : guest." << std::endl;

    if(TheGame::Instance()->P2Ready())
        std::cout << "Player2 : " << TheGame::Instance()->getP2() << "." << std::endl;
    else
        std::cout << "Player2 : guest." << std::endl;
}

// a unique ID for the MultiPlayerMenuState state used in the xml file
const std::string MultiPlayerMenuState::mStateID = "MULTI_PLAYER_MENU_STATE";
