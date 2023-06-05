#pragma once
#include "MenuState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class PauseMenuState : public MenuState
{
public:
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    virtual void setCallbacks(const std::vector<Callback>& pCallbacks);
    static void pauseToMainMenu();
    static void resumePlay();
    static void exit();
    static const std::string mPauseID;
    std::vector<GameObject*> mGameObjects;
};
