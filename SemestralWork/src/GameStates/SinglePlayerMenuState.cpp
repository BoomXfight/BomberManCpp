#include "SinglePlayerMenuState.hpp"
#include "MainMenuState.hpp"
#include "SinglePlayerPlayState.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/Game.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "../StateParser.hpp"
#include <iostream>

const std::string SinglePlayerMenuState::s_menuID = "SINGLE_PLAYER_MENU";

void SinglePlayerMenuState::setCallbacks(const std::vector<Callback> &callbacks)
{
    // go through the game objects
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void SinglePlayerMenuState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

void SinglePlayerMenuState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

bool SinglePlayerMenuState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("../src/GameStates.xml", s_menuID, &m_gameObjects,&m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(menuToQuit);
    m_callbacks.push_back(SpMenuToMainMenu);
    m_callbacks.push_back(SpMenuToSpPlay);

    setCallbacks(m_callbacks);
    std::cout << "entering SinglePlayerMenu state\n";
    return true;
}

bool SinglePlayerMenuState::onExit()
{
    if(TextSquare* a = dynamic_cast<TextSquare*>(m_gameObjects[0])) {
        TheGame::Instance()->setP1(a->getText());
        std::cout << "P1 set" << std::endl;
    }

    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
    /*
    TheTextureManager::Instance()->clearFromTextureMap("SinglePlayer");
    TheTextureManager::Instance()->clearFromTextureMap("Exit");
    TheTextureManager::Instance()->clearFromTextureMap("Back");
    TheTextureManager::Instance()->clearFromTextureMap("Bomber");
    TheTextureManager::Instance()->clearFromTextureMap("Nick");
    TheTextureManager::Instance()->clearFromTextureMap("Play");
    TheTextureManager::Instance()->clearFromTextureMap("Input");
     */
    std::cout << "exiting SinglePlayerMenuState\n";
    return true;
}

void SinglePlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

void SinglePlayerMenuState::SpMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void SinglePlayerMenuState::SpMenuToSpPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new SinglePlayerPlayState);

    if(TheGame::Instance()->P1Ready())
        std::cout << "Playing as : " << TheGame::Instance()->getP1() << std::endl;
    else
        std::cout << "Playing as : guest" << std::endl;
}

