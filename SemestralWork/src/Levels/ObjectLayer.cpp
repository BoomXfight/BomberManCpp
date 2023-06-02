#include "ObjectLayer.hpp"

void ObjectLayer::update()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->update();
}

void ObjectLayer::render()
{
    for(int i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();
}

std::vector<GameObject*>* ObjectLayer::getGameObjects()
{
    return &mGameObjects;
}
