#pragma once
#include  "Layer.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class ObjectLayer : public Layer
{
public:
    virtual void update();
    virtual void render();
    std::vector<GameObject*>* getGameObjects();

private:
    std::vector<GameObject*> m_gameObjects;
};
