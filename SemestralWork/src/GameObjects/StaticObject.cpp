#include "StaticObject.hpp"

StaticObject::StaticObject() : SDLGameObject()
{}

void StaticObject::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
}

void StaticObject::draw()
{
    SDLGameObject::draw();
}

void StaticObject::update()
{
    m_currentFrame = 0;
    SDLGameObject::update();
}

void StaticObject::clean()
{
    SDLGameObject::clean();
}