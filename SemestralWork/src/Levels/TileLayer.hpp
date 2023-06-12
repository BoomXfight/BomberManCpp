#pragma once
#include "../GameObjects/Vector2D.hpp"
#include "Layer.hpp"
#include "Level.hpp"
#include <iostream>
#include <vector>

/**
 * @class TileLayer
 * This class is responsible for the tile map part of the Level
 */
class TileLayer : public Layer
{
public:
    TileLayer(int pTileSize, const std::vector<TileSet>& pTileSets);

    /**
     * This method updates the position of the map in case of a scrolling tile map
     * Prepared for future expansion of the game.
     */
    void update() override;

    /**
     * This method renders the TileMap to the screen based on its matrix
     */
    void render() override;

    void setTileIDs(const std::vector<std::vector<int>>& pData);

    void setTileSize(int pTileSize);

    int getNumRows() const;

    int getNumCols() const;

    /**
     * This method returns a tileSet based on the ID
     * @param[in] pTileID identifier of the tile set
     * @return TileSet
     */
    TileSet getTileSetByID(int pTileID);

    /**
     * This method returns a matrix of the map
     * @return map matrix
     */
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
