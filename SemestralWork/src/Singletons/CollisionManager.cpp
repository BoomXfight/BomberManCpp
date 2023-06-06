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
    std::cout << vec.getX() << " " << vec.getY() << std::endl;
    int tileX = vec.getX() / mTileSet.mTileWidth;
    int tileY = vec.getY() / mTileSet.mTileWidth;

    std::cout << mMap[tileY][tileX] << std::endl;

    if(mMap[tileY][tileX] == 0 || mMap[tileY][tileX] == 3)
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

CollisionManager::CollisionManager() {}

CollisionManager* CollisionManager::mInstance = nullptr;
