#include "StaticObject.hpp"

StaticObject::StaticObject(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

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
