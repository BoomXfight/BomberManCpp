#pragma once
#include "GameState.hpp"
#include "MenuState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class SinglePlayerMenuState : public MenuState
{
public:
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    void setCallbacks(const std::vector<Callback>& callbacks) override;

    static void menuToQuit();
    static void spMenuToMainMenu();
    static void spMenuToSpPlay();

    std::string m_player;
    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};