#pragma once
#include "SDLGameObject.hpp"

class MenuButton : public SDLGameObject
{
public:
    MenuButton(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };
};