#pragma once
#include "MenuState.hpp"

/**
 * @class SinglePlayerWonState
 * This class implements the SinglePlayerMenuState
 */
class SinglePlayerWonState : public  MenuState
{
    /**
     * This method initializes the SinglePlayerWonState from an xml file
     * @return true -> success, false -> failed to parse a gameState file
     * @throw std::runtime_error when failed to load the GameStateFile
     */
    bool onEnter() override;

    /**
     * This method cleans up at the end of SinglePlayerWonState
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
