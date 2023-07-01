#include "StaticObject.hpp"

StaticObject::StaticObject() : SDLGameObject()
{}

void StaticObject::update()
{
    mCurrentFrame = 0;
    SDLGameObject::update();
}
