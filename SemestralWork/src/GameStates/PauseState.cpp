#include "PauseState.hpp"
#include "MainMenuState.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"
#include "../Singletons/InputHandler.hpp"
#include "../GameObjects/MenuButton.hpp"
#include "../GameObjects/StaticObject.hpp"
#include <iostream>

const std::string PauseState::s_pauseID = "PAUSE";

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
    if(!TheTextureManager::Instance()->load("../Assets/Resume.png","resumeButton", TheGame::Instance()->getRenderer())
       || !TheTextureManager::Instance()->load("../Assets/ReturnToMainMenu.png","mainButton", TheGame::Instance()->getRenderer())
       || !TheTextureManager::Instance()->load("../Assets/GamePaused.png","paused", TheGame::Instance()->getRenderer())
       || !TheTextureManager::Instance()->load("../Assets/Exit2.png","exitButton", TheGame::Instance()->getRenderer()))
        return false;

    GameObject* text = new StaticObject(new LoaderParams(200, 50, 560, 100, "paused"));
    GameObject* button1 = new MenuButton(new LoaderParams(370, 200, 200, 80, "resumeButton"), resumePlay);
    GameObject* button2 = new MenuButton(new LoaderParams(270, 300, 400, 80, "mainButton"), pauseToMainMenu);
    GameObject* button3 = new MenuButton(new LoaderParams(410, 400, 110, 80, "exitButton"), exit);
    m_gameObjects.push_back(text);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    m_gameObjects.push_back(button3);
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
