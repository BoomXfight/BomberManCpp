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

void CollisionManager::setBonuses(std::vector<Bonus*> pBonuses)
{
    mBonuses = pBonuses;
}

std::vector<Bonus*> CollisionManager::getBonuses()
{
    return mBonuses;
}

bool CollisionManager::tileCollision(Vector2D vec)
{
    int tileX = vec.getX() / mTileSet.mTileWidth;
    int tileY = vec.getY() / mTileSet.mTileWidth;

    if(mMap[tileY][tileX] == 0 || mMap[tileY][tileX] == 3 || mMap[tileY][tileX] == 7)
        return false;

    return true;
}

bool CollisionManager::isDamaged(Vector2D pVec)
{
    int tileX = pVec.getX() / mTileSet.mTileWidth;
    int tileY = pVec.getY() / mTileSet.mTileWidth;

    if(mMap[tileY][tileX] == 6)
        return true;

    return false;
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
        if(tileY + i <= mTileLayer->getNumRows() - 1 && tileY + i >= 0) // explosion down
        {
            if(mMap[tileY + i][tileX] == 1)
                downAllowed = false;
            else if(mMap[tileY + i][tileX] == 5 && downAllowed)
                mExplodedWalls += 1;

            if((mMap[tileY + i][tileX] == 3 || mMap[tileY + i][tileX] == 5) && downAllowed)
                mMap[tileY + i][tileX] = 6;
        }
        if(tileY - i <= mTileLayer->getNumRows() - 1 && tileY - i >= 0) // explosion up
        {
            if(mMap[tileY - i][tileX] == 1)
                upAllowed = false;
            else if(mMap[tileY - i][tileX] == 5 && upAllowed)
                mExplodedWalls += 1;

            if((mMap[tileY - i][tileX] == 3 || mMap[tileY - i][tileX] == 5) && upAllowed)
                mMap[tileY - i][tileX] = 6;
        }
        if(tileX + i <= mTileLayer->getNumCols() - 1 && tileX + i >= 0) // explosion right
        {
            if(mMap[tileY][tileX + i] == 1)
                rightAllowed = false;
            else if(mMap[tileY][tileX + i] == 5 && rightAllowed)
                mExplodedWalls += 1;

            if((mMap[tileY][tileX + i] == 3 || mMap[tileY][tileX + i] == 5) && rightAllowed)
                mMap[tileY][tileX + i] = 6;
        }
        if(tileX - i <= mTileLayer->getNumCols() - 1 && tileX - i >= 0) // explosion left
        {
            if(mMap[tileY][tileX - i] == 1)
                leftAllowed = false;
            else if(mMap[tileY][tileX - i] == 5 && leftAllowed)
                mExplodedWalls += 1;

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
        if (tileY + i <= mTileLayer->getNumRows() - 1 && tileY + i >= 0) // explosion down
        {
            if (mMap[tileY + i][tileX] == 6)
                mMap[tileY + i][tileX] = 3;
        }
        if (tileY - i <= mTileLayer->getNumRows() - 1 && tileY - i >= 0) // explosion up
        {
            if (mMap[tileY - i][tileX] == 6)
                mMap[tileY - i][tileX] = 3;
        }
        if (tileX + i <= mTileLayer->getNumCols() - 1 && tileX + i >= 0) // explosion right
        {
            if (mMap[tileY][tileX + i] == 6)
                mMap[tileY][tileX + i] = 3;
        }
        if (tileX - i <= mTileLayer->getNumCols() - 1 && tileX - i >= 0) // explosion left
        {
            if (mMap[tileY][tileX - i] == 6)
                mMap[tileY][tileX - i] = 3;
        }
    }
    mTileLayer->setTileIDs(mMap);
}

int CollisionManager::getResetExplodedWalls()
{
    int tmp = mExplodedWalls;
    mExplodedWalls = 0;
    return tmp;
}

CollisionManager::CollisionManager() : mExplodedWalls(0)
{}

CollisionManager* CollisionManager::mInstance = nullptr;
