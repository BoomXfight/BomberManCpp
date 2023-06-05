#pragma once
#include "GameState.hpp"
#include "MenuState.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class SinglePlayerMenuState : public MenuState
{
public:
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    void setCallbacks(const std::vector<Callback>& pCallbacks) override;

    static void menuToQuit();
    static void spMenuToMainMenu();
    static void spMenuToSpPlay();

    std::string mPlayer;
    static const std::string mMenuID;
    std::vector<GameObject*> mGameObjects;
};
