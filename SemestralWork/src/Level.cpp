#include "Level.hpp"

Level::~Level() {};

std::vector<Tileset>* Level::getTilesets()
{
    return &m_tilesets;
}

std::vector<Layer*>* Level::getLayers()
{
    return &m_layers;
}

void Level::render()
{
    for(int i = 0; i < m_layers.size(); i++)
        m_layers[i]->render();
}

void Level::update()
{
    for(int i = 0; i < m_layers.size(); i++)
        m_layers[i]->update();
}
