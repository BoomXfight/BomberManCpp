#pragma once
#include "MenuState.hpp"

/**
 * @class SinglePlayerLostState
 * This class implements the SinglePlayerLostState
 */
class SinglePlayerLostState : public  MenuState
{
    /**
     * This method initializes the SinglePlayerLostState from an xml file
     * @return true -> success, false -> failed to parse a gameState file
     * @throw std::runtime_error when failed to load the GameStateFile
     */
    bool onEnter() override;

    /**
     * This method cleans up at the end of ScoreboardState
     * @return true
     */
    bool onExit() override;

    std::string getStateID() const override;

private:
    static void playAgain();
    static void returnToMainMenu();
    static void exit();
    static const std::string mStateID;
};
