#include "PauseState.hpp"
#include "MainMenuState.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../StateParser.hpp"
#include <iostream>

const std::string PauseState::s_pauseID = "PAUSE_STATE";

void PauseState::setCallbacks(const std::vector<Callback> &callbacks)
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

void PauseState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void PauseState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("../src/GameStates.xml", s_pauseID, &m_gameObjects,&m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(resumePlay);
    m_callbacks.push_back(pauseToMainMenu);
    m_callbacks.push_back(exit);

    setCallbacks(m_callbacks);
    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    TheTextureManager::Instance()->clearFromTextureMap("resumeButton");
    TheTextureManager::Instance()->clearFromTextureMap("mainButton");
    TheTextureManager::Instance()->clearFromTextureMap("paused");
    TheTextureManager::Instance()->clearFromTextureMap("exitButton");
    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "exiting PauseState\n";
    return true;
}

void PauseState::pauseToMainMenu()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}
void PauseState::resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::exit()
{
    TheGame::Instance()->quit();
}
