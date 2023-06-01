#pragma once
#include "MenuState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class MainMenuState : public MenuState
{
public:
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    void setCallbacks(const std::vector<Callback>& callbacks) override;

    static void menuToSinglePlayer();
    static void menuToMultiPlayer();
    static void menuToQuit();

    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};