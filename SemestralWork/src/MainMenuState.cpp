#include "MainMenuState.hpp"
#include "TextureManager.hpp"
#include "MenuButton.hpp"
#include "StaticObject.hpp"
#include "PlayState.hpp"
#include "Game.hpp"
#include "SDL2/SDL.h"
#include <iostream>

const std::string MainMenuState::s_menuID = "MainMenu";

void MainMenuState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MainMenuState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter()
{
    if(!TheTextureManager::Instance()->load("../Assets/BomberMan.png", "BomberMan", TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load the button :" << SDL_GetError() << "\n";
        return false;
    }

    GameObject* bomberMan = new StaticObject(new LoaderParams(80, 20, 520, 120, "BomberMan"));
    m_gameObjects.push_back(bomberMan);
    std::cout << "entering MenuState\n";
    return true;
}

bool MainMenuState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("BomberMan");
    std::cout << "exiting MenuState\n";
    return true;
}

void MainMenuState::s_menuToSinglePlayer()
{
    std::cout << "Single Player button clicked.\n";
    TheGame ::Instance()->getStateMachine()->changeState(new PlayState());
}
