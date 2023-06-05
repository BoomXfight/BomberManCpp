#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class MenuButton : public SDLGameObject
{
public:
    MenuButton();
    void load(const LoaderParams* pParams) override;
    void draw() override;
    void update() override;
    void clean() override;
    int getCallbackID();
    void setCallback(void(*callback)());

private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    int mCallbackID;
    void (*mCallback)();
    bool mReleased;
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* createGameObject() const {return new MenuButton();}
};
