#pragma once
#include "../Levels/Level.hpp"
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
    Level* mLevel;
    static const std::string mMenuID;
    std::vector<GameObject*> mGameObjects;
};
