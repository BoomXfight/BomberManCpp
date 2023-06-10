#pragma once
#include "../GameObjects/GameObject.hpp"
#include "MenuState.hpp"

class SinglePlayerWonState : public  MenuState
{
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    static void playAgain();
    static void returnToMainMenu();
    static void exit();
    static const std::string mMenuID;
    std::vector<GameObject*> mGameObjects;
};
