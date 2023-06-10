#pragma once
#include "MenuState.hpp"

class PauseMenuState : public MenuState
{
public:
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    static void pauseToMainMenu();
    static void resumePlay();
    static void exit();
    static const std::string mPauseID;
};
