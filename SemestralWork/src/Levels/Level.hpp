#pragma once
#include "../GameObjects/Bonus.hpp"
#include "Layer.hpp"
#include <string>
#include <vector>

/**
 * @struct TileSet
 * This struct represents a tileSet of the Level map. It contains all the necessary information to render and update
 * the tile map.
 */
struct TileSet
{
    int mFirstGridID;
    int mTileWidth;
    int mTileHeight;
    int mSpacing;
    int mMargin;
    int mWidth;
    int mHeight;
    int mNumColumns;
    std::string mName;
};

/**
 * @class Level
 * This class implements a Level. It is able to load a level with any game object as well as a tile map.
 */
class Level
{
public:
    ~Level();

    /**
     * This method updates the layers of a level
     */
    void update();

    /**
     * This method renders the layers of a level
     */
    void render();

    std::vector<TileSet>* getTileSets();

    std::vector<Layer*>* getLayers();

    std::vector<Bonus*>* getBonuses();

private:
    friend class LevelParser;
    Level();

    std::vector<TileSet> mTileSets;
    std::vector<Layer*> mLayers;
    std::vector<Bonus*> mBonuses;
};
