#pragma once
#include "GameState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class PauseState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const { return s_pauseID; }

private:
    static void pauseToMainMenu();
    static void resumePlay();
    static void exit();
    static const std::string s_pauseID;
    std::vector<GameObject*> m_gameObjects;
};