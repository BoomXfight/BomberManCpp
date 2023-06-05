#include "MultiPlayerMenuState.hpp"
#include "MainMenuState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "StateParser.hpp"
#include <iostream>

/**
 * This method updates the gameObjects of the MultiPlayerMenuState
 */
void MultiPlayerMenuState::update()
{
    for(size_t i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->update();
}

/**
 * This method renders the gameObjects of the MultiPlayerMenuState
 */
void MultiPlayerMenuState::render()
{
    for(size_t i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();
}

/**
 * This method initializes the MultiPlayerMenuState from an xml file
 * @return true -> success, false -> failed to parse a gameState file
 */
bool MultiPlayerMenuState::onEnter()
{
    StateParser stateParser;
    if(! stateParser.parseState("../src/GameStates.xml", mMenuID, &mGameObjects,&mTextureIDList))
        return false;

    mCallbacks.push_back(nullptr);
    mCallbacks.push_back(menuToQuit);
    mCallbacks.push_back(mpMenuToMainMenu);
    mCallbacks.push_back(mpMenuToMpPlay);

    setCallbacks(mCallbacks);
    std::cout << "Entering MultiPlayerMenu state" << std::endl;
    return true;
}

/**
 * This method cleans up at the end of MultiPlayerMenuState and sets the active players
 * @return true
 */
bool MultiPlayerMenuState::onExit()
{
    if(TextSquare* a = dynamic_cast<TextSquare*>(mGameObjects[0]))
    {
        TheGame::Instance()->setP1(a->getText());
        std::cout << "P1 set" << std::endl;
    }

    if(TextSquare* b = dynamic_cast<TextSquare*>(mGameObjects[1]))
    {
        TheGame::Instance()->setP2(b->getText());
        std::cout << "P2 set" << std::endl;
    }

    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->clean();

    mGameObjects.clear();

    for(int i = 0; i < mTextureIDList.size(); i++)
        TheTextureManager::Instance()->clearFromTextureMap(mTextureIDList[i]);

    std::cout << "Exiting MultiPlayerMenuState" << std::endl;
    return true;
}

std::string MultiPlayerMenuState::getStateID() const
{
    return mMenuID;
}

/**
 * This method assigns a callback function to gameObjects that require it
 * @param callbacks
 */
void MultiPlayerMenuState::setCallbacks(const std::vector<Callback> &callbacks)
{
    for(int i = 0; i < mGameObjects.size(); i++)
    {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(mGameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(mGameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void MultiPlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

/**
 * Callback function to switch the current state to MainMenuState
 */
void MultiPlayerMenuState::mpMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

/**
 * Callback function to switch the current state to MultiPlayerPlayState
 */
void MultiPlayerMenuState::mpMenuToMpPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new MultiPlayerPlayState);

    if(TheGame::Instance()->P1Ready())
        std::cout << "Player1 : " << TheGame::Instance()->getP1() << std::endl;
    else
        std::cout << "Player1 : guest" << std::endl;

    if(TheGame::Instance()->P2Ready())
        std::cout << "Player2 : " << TheGame::Instance()->getP2() << std::endl;
    else
        std::cout << "Player2 : guest" << std::endl;
}

// a unique ID for the MultiPlayerMenuState state used in the xml file
const std::string MultiPlayerMenuState::mMenuID = "MULTI_PLAYER_MENU";
