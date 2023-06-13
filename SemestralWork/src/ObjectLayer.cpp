#include "ObjectLayer.hpp"

void ObjectLayer::update()
{
    for(size_t i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->update();
}

void ObjectLayer::render()
{
    for(size_t i = 0; i < mGameObjects.size(); i++)
        mGameObjects[i]->draw();
}

std::vector<GameObject*>* ObjectLayer::getGameObjects()
{
    return &mGameObjects;
}

void ObjectLayer::setGameObjects(std::vector<GameObject *> pGameObjects)
{
    mGameObjects = pGameObjects;
}
