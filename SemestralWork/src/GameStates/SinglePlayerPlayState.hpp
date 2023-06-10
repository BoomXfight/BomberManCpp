#pragma once
#include "../Levels/Level.hpp"
#include "../Levels/ObjectLayer.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class SinglePlayerPlayState : public GameState
{
public:
    virtual void update();
    virtual void render();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const;

private:
    int mLives;
    int mNoOfEnemies;
    int mPoints;

    static const std::string mPlayID;
    ObjectLayer* mObjectLayer;
    std::vector<GameObject*> mGameObjects;
    Level* mLevel;
};
