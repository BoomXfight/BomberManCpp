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

    if(mMap[tileY][tileX] == FREE || mMap[tileY][tileX] == BOMB)
        return false;

    return true;
}

bool CollisionManager::isDamaged(Vector2D pVec)
{
    int tileX = pVec.getX() / mTileSet.mTileWidth;
    int tileY = pVec.getY() / mTileSet.mTileWidth;

    if(mMap[tileY][tileX] == EXPLOSION)
        return true;

    return false;
}

void CollisionManager::placeBomb(Vector2D vec)
{
    int tileX = vec.getX() / mTileSet.mTileWidth;
    int tileY = vec.getY() / mTileSet.mTileWidth;
    mMap[tileY][tileX] = BOMB;
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
    mMap[tileY][tileX] = EXPLOSION; // middle explosion

    for(int i = 1; i <= pRadius; i++)
    {
        if(tileY + i <= mTileLayer->getNumRows() - 1 && tileY + i >= 0) // explosion down
        {
            if(mMap[tileY + i][tileX] == HARD)
                downAllowed = false;
            else if(mMap[tileY + i][tileX] == BREAKABLE && downAllowed)
                mExplodedWalls += 1;

            if((mMap[tileY + i][tileX] == FREE || mMap[tileY + i][tileX] == BREAKABLE) && downAllowed)
                mMap[tileY + i][tileX] = EXPLOSION;
        }
        if(tileY - i <= mTileLayer->getNumRows() - 1 && tileY - i >= 0) // explosion up
        {
            if(mMap[tileY - i][tileX] == HARD)
                upAllowed = false;
            else if(mMap[tileY - i][tileX] == BREAKABLE && upAllowed)
                mExplodedWalls += 1;

            if((mMap[tileY - i][tileX] == FREE || mMap[tileY - i][tileX] == BREAKABLE) && upAllowed)
                mMap[tileY - i][tileX] = EXPLOSION;
        }
        if(tileX + i <= mTileLayer->getNumCols() - 1 && tileX + i >= 0) // explosion right
        {
            if(mMap[tileY][tileX + i] == HARD)
                rightAllowed = false;
            else if(mMap[tileY][tileX + i] == BREAKABLE && rightAllowed)
                mExplodedWalls += 1;

            if((mMap[tileY][tileX + i] == FREE || mMap[tileY][tileX + i] == BREAKABLE) && rightAllowed)
                mMap[tileY][tileX + i] = EXPLOSION;
        }
        if(tileX - i <= mTileLayer->getNumCols() - 1 && tileX - i >= 0) // explosion left
        {
            if(mMap[tileY][tileX - i] == HARD)
                leftAllowed = false;
            else if(mMap[tileY][tileX - i] == BREAKABLE && leftAllowed)
                mExplodedWalls += 1;

            if((mMap[tileY][tileX - i] == FREE || mMap[tileY][tileX - i] == BREAKABLE) && leftAllowed)
                mMap[tileY][tileX - i] = EXPLOSION;
        }
    }
    mTileLayer->setTileIDs(mMap);
}

void CollisionManager::afterExplosion(Vector2D pVec, int pRadius)
{
    int tileX = pVec.getX() / mTileSet.mTileWidth;
    int tileY = pVec.getY() / mTileSet.mTileWidth;
    mMap[tileY][tileX] = FREE;

    for(int i = 1; i <= pRadius; i++)
    {
        if (tileY + i <= mTileLayer->getNumRows() - 1 && tileY + i >= 0) // explosion down
        {
            if (mMap[tileY + i][tileX] == EXPLOSION)
                mMap[tileY + i][tileX] = FREE;
        }
        if (tileY - i <= mTileLayer->getNumRows() - 1 && tileY - i >= 0) // explosion up
        {
            if (mMap[tileY - i][tileX] == EXPLOSION)
                mMap[tileY - i][tileX] = FREE;
        }
        if (tileX + i <= mTileLayer->getNumCols() - 1 && tileX + i >= 0) // explosion right
        {
            if (mMap[tileY][tileX + i] == EXPLOSION)
                mMap[tileY][tileX + i] = FREE;
        }
        if (tileX - i <= mTileLayer->getNumCols() - 1 && tileX - i >= 0) // explosion left
        {
            if (mMap[tileY][tileX - i] == EXPLOSION)
                mMap[tileY][tileX - i] = FREE;
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
