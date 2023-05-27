#pragma once
#include "GameState.hpp"
#include "GameObject.hpp"
#include <vector>

class MainMenuState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const { return s_menuID; }

private:
    static void menuToSinglePlayer();
    static void menuToMultiPlayer();
    static void menuToQuit();

    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};