#pragma once
#include "../GameObjects/Bonus.hpp"
#include "Layer.hpp"
#include <string>
#include <vector>

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

class Level
{
public:
    ~Level();
    void update();
    void render();
    std::vector<TileSet>* getTileSets();
    std::vector<Layer*>* getLayers();
    std::vector<Bonus*>* getBonuses();

private:
    friend class LevelParser;
    Level()  {}

    std::vector<TileSet> mTileSets;
    std::vector<Layer*> mLayers;
    std::vector<Bonus*> mBonuses;
};
