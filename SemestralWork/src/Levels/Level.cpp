#include "Level.hpp"

Level::~Level() = default;

void Level::update()
{
    for(int i = 0; i < mLayers.size(); i++)
        mLayers[i]->update();
}

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

std::vector<Bonus*>* Level::getBonuses()
{
    return &mBonuses;
}

Level::Level() = default;
