#pragma once
#include "GameState.hpp"
#include "MenuState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class SinglePlayerMenuState : public MenuState
{
public:
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    static void menuToQuit();
    static void spMenuToMainMenu();
    static void spMenuToSpPlay();

    std::string mPlayer;
    static const std::string mStateID;
};
