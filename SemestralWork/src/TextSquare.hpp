#pragma once
#include "GameObjectFactory.hpp"
#include "SDLGameObject.hpp"

/**
 * @class TextSquare
 * TextSquare class is responsible for every text box inside the game.
 * It allows user to write inside of the text box when activate.
 */
class TextSquare : public SDLGameObject
{
public:
    TextSquare();

    /**
     * This method draws a text written by the player to the screen
     */
    void draw() override;

    /**
     * This method activates the text detection and handles the text input
     */
    void update() override;

    /**
     * This method loads the StaticObject
     * @param pParams loading parameters
     */
    void load(const LoaderParams* pParams) override;

    virtual std::string getText();

private:
    enum button_state
    {
        NOT_CLICKED = 0,
        CLICKED = 1
    };

    /**
     * This method handles the user's text input. It activates the text square when clicked.
     * It detects the user's text input and saves it to the member variable.
     */
    void handleInput();

    bool mActive;
    bool mReleased;
    std::string mText;
};

/**
 * @class TextSquareCreator
 * This class is responsible for the creation of the TextSquare object
 */
class TextSquareCreator : public BaseCreator
{
    /**
     * This method creates a new TextSquare object
     * @return TextSquare object
     */
    GameObject* createGameObject() const override {return new TextSquare();}
};
