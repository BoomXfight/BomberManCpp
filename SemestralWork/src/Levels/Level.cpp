#include "Level.hpp"

Level::~Level() {};

/**
 * This method updates the layers of a level
 */
void Level::update()
{
    for(int i = 0; i < m_layers.size(); i++)
        m_layers[i]->update();
}

/**
 * This method renders the layers of a level
 */
void Level::render()
{
    for(int i = 0; i < m_layers.size(); i++)
        m_layers[i]->render();
}

std::vector<Tileset>* Level::getTilesets()
{
    return &m_tilesets;
}

std::vector<Layer*>* Level::getLayers()
{
    return &m_layers;
}
