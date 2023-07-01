#pragma once
#include "MenuState.hpp"

/**
 * @class PauseMenuState
 * This class handles the PauseMenuState
 */
class PauseMenuState : public MenuState
{
public:
    /**
     * This method initializes the PauseMenuState from an xml file
     * @return true -> success, false -> failed to parse a gameState file
     * @throw std::runtime_error when failed to load the GameStateFile
     */
    bool onEnter() override;

    /**
     * This method cleans up at the end of PauseMenuState
     * @return true
     */
    bool onExit() override;

    std::string getStateID() const override;

private:
    static void pauseToMainMenu();
    static void resumePlay();
    static void exit();
    static const std::string mPauseID;
};
