#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class StaticObject : public SDLGameObject
{
public:
    StaticObject();
    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
};

class StaticObjectCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new StaticObject();
    }
};
