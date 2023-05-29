#include "MultiPlayerMenuState.hpp"
#include "MainMenuState.hpp"
#include "MultiPlayerPlayState.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../GameObjects/StaticObject.hpp"
#include "../GameObjects/TextSquare.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../StateParser.hpp"
#include <iostream>

const std::string MultiPlayerMenuState::s_menuID = "MULTI_PLAYER_MENU";

void MultiPlayerMenuState::setCallbacks(const std::vector<Callback> &callbacks)
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

void MultiPlayerMenuState::update()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

void MultiPlayerMenuState::render()
{
    for(size_t i = 0; i < m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();
}

bool MultiPlayerMenuState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("../src/GameStates.xml", s_menuID, &m_gameObjects,&m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(menuToQuit);
    m_callbacks.push_back(MpMenuToMainMenu);
    m_callbacks.push_back(MpMenuToMpPlay);

    setCallbacks(m_callbacks);
    std::cout << "entering MultiPlayerMenu state\n";
    return true;
}

bool MultiPlayerMenuState::onExit()
{
    if(TextSquare* a = dynamic_cast<TextSquare*>(m_gameObjects[0])) {
        TheGame::Instance()->setP1(a->getText());
        std::cout << "P1 set" << std::endl;
    }

    if(TextSquare* b = dynamic_cast<TextSquare*>(m_gameObjects[1])) {
        TheGame::Instance()->setP2(b->getText());
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
    std::cout << "exiting MultiPlayerMenuState\n";
    return true;
}

void MultiPlayerMenuState::menuToQuit()
{
    TheGame::Instance()->quit();
}

void MultiPlayerMenuState::MpMenuToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState);
}

void MultiPlayerMenuState::MpMenuToMpPlay()
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
