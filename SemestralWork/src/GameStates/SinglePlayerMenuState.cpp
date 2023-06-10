#include "SinglePlayerMenuState.hpp"
#include "MainMenuState.hpp"
#include "SinglePlayerPlayState.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/Game.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "StateParser.hpp"
#include <iostream>

/**
 * This method updates the gameObjects of the SinglePlayerMenuState
 */
void SinglePlayerMenuState::update()
{
    for(size_t i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->update();
}

/**
 * This method renders the gameObject of the SinglePlayerMenuState
 */
void SinglePlayerMenuState::render()
{
    for(size_t i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();
}

/**
 * This method initializes the SinglePlayerMenuState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool SinglePlayerMenuState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mMenuID, &mGameObjects,&mTextureIDList))
        return false;

    mCallbacks.push_back(nullptr);
    mCallbacks.push_back(menuToQuit);
    mCallbacks.push_back(spMenuToMainMenu);
    mCallbacks.push_back(spMenuToSpPlay);

    setCallbacks(mCallbacks);
    std::cout << "Entering SinglePlayerMenu state" << std::endl;
    return true;
}

/**
 * This method cleans up at the end of SinglePlayerMenuState and initializes an active player
 * @return true
 */
bool SinglePlayerMenuState::onExit()
{
    if(TextSquare* a = dynamic_cast<TextSquare*>(mGameObjects[0]))
    {
        TheGame::Instance()->setP1(a->getText());
        std::cout << "P1 set" << std::endl;
    }

    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting SinglePlayerMenuState" << std::endl;
    return true;
}

std::string SinglePlayerMenuState::getStateID() const
{
    return mMenuID;
}

/**
 * This callback function quits the game
 */
void SinglePlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

/**
 * This callback function returns to the MainMenuState
 */
void SinglePlayerMenuState::spMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

/**
 * This callback function switches from SinglePlayerMenuState to the SinglePlayerPlayState
 */
void SinglePlayerMenuState::spMenuToSpPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerPlayState);

    if(TheGame::Instance()->P1Ready())
        std::cout << "Playing as : " << TheGame::Instance()->getP1() << std::endl;
    else
        std::cout << "Playing as : guest" << std::endl;
}

// a unique ID for SinglePlayerPlayState used in the xml file
const std::string SinglePlayerMenuState::mMenuID = "SINGLE_PLAYER_MENU_STATE";
