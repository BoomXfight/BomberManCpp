#pragma once
#include "../GameObjects/GameObject.hpp"
#include "../Levels/Level.hpp"
#include "ScoreboardState.hpp"
#include "GameState.hpp"
#include "SDL2/SDL.h"
#include <vector>

class MultiPlayerPlayState : public GameState
{
public:
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    void handlePlayers();
    void handlePlayer1Information() const;
    void handlePlayer2Information() const;
    void updatePlayersScore(std::vector<PlayerScore>& pScores);

    int mP1Score;
    int mP2Score;
    int mP1Lives;
    int mP2Lives;
    int mP1Speed;
    int mP2Speed;
    int mP1Radius;
    int mP2Radius;
    bool mP1Immortal;
    bool mP2Immortal;
    bool mP1BombTime;
    bool mP2BombTime;
    bool mP1Dmg;
    bool mP2Dmg;

    Uint32 mDmg1Timer;
    Uint32 mDmg2Timer;
    Uint32 mNow;

    static const std::string mStateID;
    Level* mLevel;
};
