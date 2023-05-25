#include "MenuState.hpp"
#include "TextureManager.hpp"
#include "MenuButton.hpp"
#include "Game.hpp"
#include "SDL2/SDL.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MenuState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter()
{
    if(!TheTextureManager::Instance()->load("Assets/Finished/SinglePlayerSS.png", "SinglePlayer", TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load the button :" << SDL_GetError() << "\n";
        return false;
    }

    GameObject* button1 = new MenuButton(new LoaderParams(0, 0, 300, 80, "SinglePlayer"), s_menuToSinglePlayer);
    m_gameObjects.push_back(button1);
    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("SPButton");
    std::cout << "exiting MenuState\n";
    return true;
}

void MenuState::s_menuToSinglePlayer()
{
    std::cout << "Single Player button clicked.\n";
}
