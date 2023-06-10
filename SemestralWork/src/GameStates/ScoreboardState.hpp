#pragma once
#include "../GameObjects/GameObject.hpp"
#include "MenuState.hpp"

struct PlayerScore
{
    std::string name;
    int score;
};

bool comparePlayers(const PlayerScore& p1, const PlayerScore& p2);

class ScoreboardState : public MenuState
{
public:
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    static void scoreboardToMainMenu();
    static void exit();
    static const std::string mMenuID;
    std::vector<GameObject*> mGameObjects;
    std::vector<PlayerScore> mPlayers;
};
