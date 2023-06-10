#pragma once
#include "MenuState.hpp"

class MultiPlayerMenuState : public MenuState
{
public:
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    static void menuToQuit();
    static void mpMenuToMainMenu();
    static void mpMenuToMpPlay();

    static const std::string mStateID;
};
