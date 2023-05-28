#pragma once
#include "../GameObjects/SDLGameObject.hpp"

class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    void handleInput();
};