#pragma once
#include "GameState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>


class MultiPlayerPlayState : public GameState
{

public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const {return s_menuID;};

private:
    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};
