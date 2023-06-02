#pragma once
#include "Layer.hpp"
#include "Level.hpp"
#include "../Vector2D.hpp"
#include <iostream>
#include <vector>

class TileLayer : public Layer
{
public:
    TileLayer(int pTileSize, const std::vector<TileSet>& pTileSets);

    virtual void update();
    virtual void render();

    void setTileIDs(const std::vector<std::vector<int>>& pData);
    void setTileSize(int pTileSize);
    TileSet getTileSetByID(int pTileID);

private:
    int mNumColumns;
    int mNumRows;
    int mTileSize;

    Vector2D mPosition;
    Vector2D mVelocity;

    const std::vector<TileSet>& mTileSets;
    std::vector<std::vector<int>> mTileIDs;
};
