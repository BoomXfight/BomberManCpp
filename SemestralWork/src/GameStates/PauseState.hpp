#pragma once
#include "MenuState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class PauseState : public MenuState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const { return s_pauseID; }

private:
    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    static void pauseToMainMenu();
    static void resumePlay();
    static void exit();
    static const std::string s_pauseID;
    std::vector<GameObject*> m_gameObjects;
};