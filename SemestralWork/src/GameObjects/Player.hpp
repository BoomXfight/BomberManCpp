#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class Player : public SDLGameObject
{
public:
    Player();
    void load(const LoaderParams *pParams) override;
    void draw() override;
    void update() override;
    void clean() override;

private:
    void handleInput();
    bool moving;
};

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};
