#pragma once
#include "MenuState.hpp"

/**
 * @class SinglePlayerMenuState
 * This class implements the SinglePlayerMenuState
 */
class SinglePlayerMenuState : public MenuState
{
public:
    /**
     * This method initializes the SinglePlayerMenuState from an xml file
     * @return true -> success, false -> failed to parse a gameState file
     * @throw std::runtime_error when failed to load the GameStateFile
     */
    bool onEnter() override;

    /**
     * This method cleans up at the end of SinglePlayerMenuState and sets the player of the next PlayState
     * @return true
     */
    bool onExit() override;

    std::string getStateID() const override;

private:
    static void menuToQuit();
    static void spMenuToMainMenu();
    static void spMenuToSpPlay();

    std::string mPlayer;
    static const std::string mStateID;
};
