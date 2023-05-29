#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class TextSquare : public SDLGameObject
{
public:
    TextSquare();
    virtual void load(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual std::string getText();

private:
    enum button_state
    {
        NOT_CLICKED = 0,
        CLICKED = 1
    };

    void handleInput();
    std::string m_text;
    bool active;
    bool m_bReleased;
};

class TextSquareCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new TextSquare();
    }
};
