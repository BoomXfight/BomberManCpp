#pragma once
#include "SDLGameObject.hpp"
#include "GameObjectFactory.hpp"

/**
 * @class MenuButton
 * This is a MenuButton class responsible for buttons inside the MenuStates
 * The button can be clicked, hovered over, not touched by mouse
 */
class MenuButton : public SDLGameObject
{
public:
    MenuButton();

    /**
     * This method implements the dynamics of the button, swapping its states based on the position of the mouse
     */
    void update() override;

    /**
     * This method loads the MenuButton object
     * @param[in] pParams
     */
    void load(const LoaderParams* pParams) override;

    int getCallbackID() const;

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

/**
 * @class MenuButtonCreator
 * This class is responsible for the creation of the MenuButton object
 */
class MenuButtonCreator : public BaseCreator
{
    /**
     * This method creates a new MenuButton object
     * @return MenuButton
     */
    GameObject* createGameObject() const override {return new MenuButton();}
};
