#pragma once
#include "../Levels/Level.hpp"
#include "../Levels/ObjectLayer.hpp"
#include "../GameObjects/GameObject.hpp"
#include "ScoreboardState.hpp"
#include <vector>

class SinglePlayerPlayState : public GameState
{
public:
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    void updatePlayer();
    void handleGameInformation();
    void updatePlayersScore(std::vector<PlayerScore>& pScores);

    int mLives;
    int mSpeed;
    int mRadius;
    int mNoOfEnemies;
    int mScore;
    bool mBombTime;
    bool mImmortal;

    static const std::string mStateID;
    ObjectLayer* mObjectLayer;
    std::vector<GameObject*> mGameObjects;
    Level* mLevel;
};
