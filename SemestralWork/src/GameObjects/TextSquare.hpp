#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class TextSquare : public SDLGameObject
{
public:
    TextSquare();
    void load(const LoaderParams* pParams) override;
    void draw() override;
    void update() override;
    void clean() override;
    virtual std::string getText();

private:
    enum button_state
    {
        NOT_CLICKED = 0,
        CLICKED = 1
    };

    void handleInput();
    std::string mText;
    bool mActive;
    bool mReleased;
};

class TextSquareCreator : public BaseCreator
{
    GameObject* createGameObject() const {return new TextSquare();}
};
