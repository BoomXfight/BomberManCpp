#pragma once
#include "SDLGameObject.hpp"

class Enemy : public SDLGameObject
{
public:
    Enemy();
    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    void handleInput();
};