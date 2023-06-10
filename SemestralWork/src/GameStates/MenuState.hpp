#pragma once
#include "../GameObjects/GameObject.hpp"
#include "GameState.hpp"


class MenuState : public GameState
{
public:
    MenuState();
    void update() override;
    void render() override;

protected:
    typedef void(*Callback)();
    void setCallbacks(const std::vector<Callback>& pCallbacks);

    std::vector<Callback> mCallbacks;
    std::vector<GameObject*> mGameObjects;
};
