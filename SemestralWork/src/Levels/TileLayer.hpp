#pragma once
#include "Layer.hpp"
#include "Level.hpp"
#include "../Vector2D.hpp"
#include <iostream>
#include <vector>
#include <memory>

class TileLayer : public Layer
{
public:
    TileLayer(int pTileSize, const std::vector<TileSet>& pTileSets);

    void update() override;
    void render() override;

    void setTileIDs(const std::vector<std::vector<int>>& pData);
    void setTileSize(int pTileSize);
    int getNumRows();
    int getNumCols();
    TileSet getTileSetByID(int pTileID);
    std::vector<std::vector<int>> getTileIDs();

private:
    int mNumColumns;
    int mNumRows;
    int mTileSize;

    Vector2D mPosition;
    Vector2D mVelocity;

    const std::vector<TileSet>& mTileSets;
    std::vector<std::vector<int>> mTileIDs;
};
