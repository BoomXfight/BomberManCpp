#include "CollisionManager.hpp"

CollisionManager* CollisionManager::Instance()
{
    if(mInstance == nullptr)
        mInstance = new CollisionManager();

    return mInstance;
}

void CollisionManager::setTileLayer(TileLayer* pObjectLayer)
{
    mTileLayer = pObjectLayer;
    mMap = mTileLayer->getTileIDs();
    mTileSet = mTileLayer->getTileSetByID(1);
}

void CollisionManager::setObjectLayer(ObjectLayer *pObjectLayer)
{
    mObjectLayer = pObjectLayer;
    mGameObjects = mObjectLayer->getGameObjects();
}

bool CollisionManager::tileCollision(Vector2D vec)
{
    int tileX = vec.getX() / mTileSet.mTileWidth;
    int tileY = vec.getY() / mTileSet.mTileWidth;

    if(mMap[tileY][tileX] == 0 || mMap[tileY][tileX] == 3 || mMap[tileY][tileX] == 7)
        return false;

    return true;
}

void CollisionManager::placeBomb(Vector2D vec)
{
    int tileX = vec.getX() / mTileSet.mTileWidth;
    int tileY = vec.getY() / mTileSet.mTileWidth;
    mMap[tileY][tileX] = 7;
    mTileLayer->setTileIDs(mMap);
}

void CollisionManager::explodeBomb(Vector2D pVec, int pRadius)
{
    bool rightAllowed = true;
    bool leftAllowed = true;
    bool upAllowed = true;
    bool downAllowed = true;

    int tileX = pVec.getX() / mTileSet.mTileWidth;
    int tileY = pVec.getY() / mTileSet.mTileWidth;
    mMap[tileY][tileX] = 6; // middle explosion

    for(int i = 1; i <= pRadius; i++)
    {
        if(tileY + i <= mTileSet.mTileHeight && tileY + i >= 0) // explosion down
        {
            if(mMap[tileY + i][tileX] == 1)
                downAllowed = false;

            if((mMap[tileY + i][tileX] == 3 || mMap[tileY + i][tileX] == 5) && downAllowed)
                mMap[tileY + i][tileX] = 6;
        }
        if(tileY - i <= mTileSet.mTileHeight && tileY - i >= 0) // explosion up
        {
            if(mMap[tileY - i][tileX] == 1)
                upAllowed = false;

            if((mMap[tileY - i][tileX] == 3 || mMap[tileY - i][tileX] == 5) && upAllowed)
                mMap[tileY - i][tileX] = 6;
        }
        if(tileX + i <= mTileSet.mTileHeight && tileX + i >= 0) // explosion right
        {
            if(mMap[tileY][tileX + i] == 1)
                rightAllowed = false;

            if((mMap[tileY][tileX + i] == 3 || mMap[tileY][tileX + i] == 5) && rightAllowed)
                mMap[tileY][tileX + i] = 6;
        }
        if(tileX - i <= mTileSet.mTileHeight && tileX - i >= 0) // explosion left
        {
            if(mMap[tileY][tileX - i] == 1)
                leftAllowed = false;

            if((mMap[tileY][tileX - i] == 3 || mMap[tileY][tileX - i] == 5) && leftAllowed)
                mMap[tileY][tileX - i] = 6;
        }
    }
    mTileLayer->setTileIDs(mMap);
}

void CollisionManager::afterExplosion(Vector2D pVec, int pRadius)
{
    int tileX = pVec.getX() / mTileSet.mTileWidth;
    int tileY = pVec.getY() / mTileSet.mTileWidth;
    mMap[tileY][tileX] = 3;

    for(int i = 1; i <= pRadius; i++)
    {
        if (tileY + i <= mTileSet.mTileHeight && tileY + i >= 0) // explosion down
        {
            if (mMap[tileY + i][tileX] == 6)
                mMap[tileY + i][tileX] = 3;
        }
        if (tileY - i <= mTileSet.mTileHeight && tileY - i >= 0) // explosion up
        {
            if (mMap[tileY - i][tileX] == 6)
                mMap[tileY - i][tileX] = 3;
        }
        if (tileX + i <= mTileSet.mTileHeight && tileX + i >= 0) // explosion right
        {
            if (mMap[tileY][tileX + i] == 6)
                mMap[tileY][tileX + i] = 3;
        }
        if (tileX - i <= mTileSet.mTileHeight && tileX - i >= 0) // explosion left
        {
            if (mMap[tileY][tileX - i] == 6)
                mMap[tileY][tileX - i] = 3;
        }
    }
    mTileLayer->setTileIDs(mMap);
}

CollisionManager::CollisionManager() {}

CollisionManager* CollisionManager::mInstance = nullptr;
