#pragma once
#include "GameState.hpp"
#include "SDL2/SDL.h"
#include "../Levels/Level.hpp"
#include "../GameObjects/GameObject.hpp"
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
    int mP1Lives;
    int mP2Lives;
    int mP1Score;
    int mP2Score;
    bool mP1Dmg;
    bool mP2Dmg;

    Uint32 mDmg1Timer;
    Uint32 mDmg2Timer;
    Uint32 mNow;

    static const std::string mPlayID;
    Level* mLevel;
};
