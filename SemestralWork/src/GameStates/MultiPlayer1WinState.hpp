#pragma once
#include "MenuState.hpp"

class MultiPlayer1WinState : public MenuState
{
public:
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    static void playAgain();
    static void returnToMainMenu();
    static void exit();
    static const std::string mStateID;
};
