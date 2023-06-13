#include "Enemy.hpp"
#include "CollisionManager.hpp"

CollisionManager* CollisionManager::Instance()
{
    if(mInstance == nullptr)
        mInstance = new CollisionManager();

    return mInstance;
}

void CollisionManager::setTileLayer(TileLayer* pTileLayer)
{
    mTileLayer = pTileLayer;
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

bool CollisionManager::tileCollisionPlayer(Vector2D pVec)
{
    int tileX = pVec.getX() / mTileSet.mTileWidth;
    int tileY = pVec.getY() / mTileSet.mTileWidth;

    if(mMap[tileY][tileX] == FREE || mMap[tileY][tileX] == BOMB)
        return false;

    return true;
}

bool CollisionManager::enemyCollisionPlayer(Player* pPlayer)
{
    for(auto it = mGameObjects->begin(); it != mGameObjects->end(); it++)
    {
        //dynamic_cast<MenuButton*>(mGameObjects[i])
        if(dynamic_cast<Enemy*>(*it))
        {
            Enemy* enemy = dynamic_cast<Enemy*>(*it);
            if (pPlayer->getPosition().getY() + pPlayer->getHeight() < enemy->getPosition().getY()) // vertical
                continue;

            else if(pPlayer->getPosition().getY() > enemy->getPosition().getY() + enemy->getHeight()) // vertical
                continue;

            else if(pPlayer->getPosition().getX() + pPlayer->getWidth() < enemy->getPosition().getX()) // horizontal
                continue;

            else if(pPlayer->getPosition().getX() > enemy->getPosition().getX() + enemy->getWidth())
                continue;

            else
                return true;
        }
    }
    return false;
}

bool CollisionManager::tileCollisionEnemy(Vector2D pVec)
{
    int tileX = pVec.getX() / mTileSet.mTileWidth;
    int tileY = pVec.getY() / mTileSet.mTileWidth;

    if(mMap[tileY][tileX] == FREE)
        return false;

    return true;
}

bool CollisionManager::isPlayerDamaged(Vector2D pVec)
{
    int tileX = pVec.getX() / mTileSet.mTileWidth;
    int tileY = pVec.getY() / mTileSet.mTileWidth;

    if(mMap[tileY][tileX] == EXPLOSION)
        return true;

    return false;
}

bool CollisionManager::isEnemyHit(Vector2D pVec)
{
    int tileX = pVec.getX() / mTileSet.mTileWidth;
    int tileY = pVec.getY() / mTileSet.mTileWidth;

    if(mMap[tileY][tileX] == EXPLOSION)
    {
        for (auto it = mGameObjects->begin(); it != mGameObjects->end(); it++) {
            if (dynamic_cast<Enemy *>(*it))
            {
                Enemy* enemy = dynamic_cast<Enemy*>(*it);
                if(enemy->getPosition().getX() == pVec.getX()
                && enemy->getPosition().getY() == pVec.getY()) {
                    mGameObjects->erase(it);
                    break;
                }
            }
        }
        mObjectLayer->setGameObjects(*mGameObjects);
        return true;
    }
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
