#pragma once
#include "SDLGameObject.hpp"

class StaticObject : public SDLGameObject
{
public:
    StaticObject(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
};
