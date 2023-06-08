#include "TileLayer.hpp"
#include "../Singletons/Game.hpp"
#include "../Singletons/TextureManager.hpp"

TileLayer::TileLayer(int pTileSize, const std::vector<TileSet>& pTileSets)
    : mTileSize(pTileSize), mTileSets(pTileSets), mPosition(0, 0), mVelocity(0, 0)
{
    mType = "Tile";
    mNumColumns = (TheGame::Instance()->getGameWidth() / mTileSize);
    mNumRows = (TheGame::Instance()->getGameHeight() / mTileSize);
}

void TileLayer::update()
{
    mPosition += mVelocity;
}

void TileLayer::render()
{
    int x, y, x2, y2 = 0;

    x = mPosition.getX() / mTileSize;
    y = mPosition.getY() / mTileSize;

    x2 = int(mPosition.getX()) % mTileSize;
    y2 = int(mPosition.getY()) % mTileSize;

    for(int i = 0; i < mNumRows; i++)
    {
        for(int j = 0; j < mNumColumns; j++)
        {
            int id = mTileIDs[i + y][j + x];
            if(id == 0)
                continue;

            TileSet tileSet = getTileSetByID(id);
            id--;

            TheTextureManager::Instance()->drawTile(tileSet.mName, tileSet.mMargin, tileSet.mSpacing,
                                                    (j * mTileSize) - x2, (i * mTileSize) - y2,
                                                    mTileSize,mTileSize,
                                                    (id - (tileSet.mFirstGridID - 1)) / tileSet.mNumColumns,
                                                    (id - (tileSet.mFirstGridID - 1)) % tileSet.mNumColumns,
                                                    TheGame::Instance()->getRenderer());
        }
    }
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& pData)
{
    mTileIDs = pData;
}

void TileLayer::setTileSize(int pTileSize)
{
    mTileSize = pTileSize;
}

int TileLayer::getNumRows()
{
    return mNumRows;
}

int TileLayer::getNumCols()
{
    return mNumColumns;
}

TileSet TileLayer::getTileSetByID(int pTileID)
{
    for (int i = 0; i < mTileSets.size(); i++)
    {
        if (i + 1 <= mTileSets.size() - 1)
        {
            if (pTileID >= mTileSets[i].mFirstGridID && pTileID < mTileSets[i + 1].mFirstGridID)
                return mTileSets[i];
        }
        else
            return mTileSets[i];
    }

    std::cout << "Did not find the TileSet, returning empty TileSet" << std::endl;
    TileSet t;
    return t;
}

std::vector<std::vector<int>> TileLayer::getTileIDs()
{
    return mTileIDs;
}
