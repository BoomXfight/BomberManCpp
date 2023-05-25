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
    if(! TheTextureManager::Instance()->load("TO DO PATH", "buttons", TheGame::Instance()->getRenderer()))
    {
        std::cout << "Failed to load the button :" << SDL_GetError() << "\n";
        return false;
    }
    GameObject* button1 = new MenuButton(new LoaderParams(0, 0, 400, 200, "buttons"));
    GameObject* button2 = new MenuButton(new LoaderParams(1000, 600, 400, 200, "buttons"));
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
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
    TheTextureManager::Instance()->clearFromTextureMap("buttons");
    std::cout << "exiting MenuState\n";
    return true;
}