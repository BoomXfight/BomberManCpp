#pragma once
#include "SDLGameObject.hpp"

class TextSquare : public SDLGameObject
{
public:
    TextSquare(const LoaderParams* pParams);
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
    bool m_bReleased;
};