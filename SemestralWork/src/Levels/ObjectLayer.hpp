#pragma once
#include  "Layer.hpp"
#include "../GameObjects/GameObject.hpp"
#include <vector>

class ObjectLayer : public Layer
{
public:
    void update() override;
    void render() override;
    std::vector<GameObject*>* getGameObjects();
    void setGameObjects(std::vector<GameObject*> pGameObjects);

private:
    std::vector<GameObject*> mGameObjects;
};
