#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class StaticObject : public SDLGameObject
{
public:
    StaticObject();
    void load(const LoaderParams *pParams) override;
    void draw() override;
    void update() override;
    void clean() override;
};

class StaticObjectCreator : public BaseCreator
{
    GameObject* createGameObject() const {return new StaticObject();}
};
