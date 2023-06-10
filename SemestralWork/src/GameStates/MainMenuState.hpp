#pragma once
#include "MenuState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class MainMenuState : public MenuState
{
public:
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    static void menuToSinglePlayer();
    static void menuToMultiPlayer();
    static void menuToScoreboard();
    static void menuToQuit();

    static const std::string mStateID;
};
