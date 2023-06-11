#pragma once
#include "MenuState.hpp"
#include <vector>

/**
 * @class MainMenuState
 * This class is responsible for creation, handling and deletion of MainMenuState -> the main state of the game
 */
class MainMenuState : public MenuState
{
public:
    /**
     * This method initializes the MainMenuState
     * @return true-> success, false->failure
     * @throw std::runtime_error when failed to load the GameStateFile
     */
    bool onEnter() override;

    /**
     * This method cleans up at the end of MainMenuState
     * @return true
     */
    bool onExit() override;

    std::string getStateID() const override;

private:
    static void menuToSinglePlayer();
    static void menuToMultiPlayer();
    static void menuToScoreboard();
    static void menuToQuit();

    static const std::string mStateID;
};
