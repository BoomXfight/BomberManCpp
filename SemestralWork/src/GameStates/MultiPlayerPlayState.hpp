#pragma once
#include "GameState.hpp"
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
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
    Level* pLevel;
};
