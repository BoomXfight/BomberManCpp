#pragma once
#include "../Singletons/TextureManager.hpp"
#include "GameObject.hpp"
#include "../Vector2D.hpp"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject();
    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width;
    int m_height;
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;
};