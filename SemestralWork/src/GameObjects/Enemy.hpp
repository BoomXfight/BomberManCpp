#pragma once
#include "../Singletons/GameObjectFactory.hpp"
#include "SDLGameObject.hpp"

class Enemy : public SDLGameObject {
public:
    Enemy();
    void draw() override;
    void update() override;
    void clean() override;
    void load(const LoaderParams *pParams) override;

private:
    void handleMovement();

    float mSpeed;
    float mBuffer;

    bool mMoveUp;

};

class EnemyCreator : public BaseCreator
{
    GameObject* createGameObject() const {return new Enemy();};
};
