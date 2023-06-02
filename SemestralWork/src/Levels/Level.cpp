#include "Level.hpp"

Level::~Level() {};

/**
 * This method updates the layers of a level
 */
void Level::update()
{
    for(int i = 0; i < mLayers.size(); i++)
        mLayers[i]->update();
}

/**
 * This method renders the layers of a level
 */
void Level::render()
{
    for(int i = 0; i < mLayers.size(); i++)
        mLayers[i]->render();
}

std::vector<TileSet>* Level::getTileSets()
{
    return &mTileSets;
}

std::vector<Layer*>* Level::getLayers()
{
    return &mLayers;
}
