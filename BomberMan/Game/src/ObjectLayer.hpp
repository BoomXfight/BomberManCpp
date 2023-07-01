#pragma once
#include "Layer.hpp"
#include "GameObject.hpp"
#include <vector>

/**
 * @class ObjectLayer
 * This class holds GameObject layer of the Level
 */
class ObjectLayer : public Layer
{
public:
    /**
     * This method updates the GameObject of the layer
     */
    void update() override;

    /**
     * This method renders the GameObject of the layer to the screen
     */
    void render() override;

    std::vector<GameObject*>* getGameObjects();

    void setGameObjects(std::vector<GameObject*> pGameObjects);

private:
    std::vector<GameObject*> mGameObjects;
};
