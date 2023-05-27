#pragma once
#include "GameState.hpp"
#include "GameObject.hpp"
#include <vector>

class SinglePlayerMenuState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const {return s_menuID;};

private:
    static void menuToQuit();
    static void SpMenuToMainMenu();
    static void SpMenuToSpPlay();

    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};