#pragma once
#include "MenuState.hpp"

/**
 * @class MultiPlayer1WinState
 * This class handles the state that is designed for player1 win in the multi-player mode
 */
class MultiPlayer1WinState : public MenuState
{
public:
    /**
     * This method initializes the MultiPlayer1WinState from an xml file
     * @return true -> success, false -> failed to parse a gameState file
     * @throw std::runtime_error when failed to load the GameStateFile
     */
    bool onEnter() override;

    /**
     * This method cleans up at the end of MultiPlayer1WinState
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
