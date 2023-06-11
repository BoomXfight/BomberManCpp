#pragma once
#include "MenuState.hpp"

/**
 * @class MultiPlayerMenuState
 * This class handles the MultiPlayerMenuState
 */
class MultiPlayerMenuState : public MenuState
{
public:
    /**
     * This method initializes the MultiPlayerMenuState from an xml file
     * @return true -> success, false -> failed to parse a gameState file
     * @throw std::runtime_error when failed to load the GameStateFile
     */
    bool onEnter() override;

    /**
     * This method cleans up at the end of MultiPlayerMenuState
     * @return true
     */
    bool onExit() override;

    std::string getStateID() const override;

private:
    static void menuToQuit();
    static void mpMenuToMainMenu();
    static void mpMenuToMpPlay();

    static const std::string mStateID;
};
