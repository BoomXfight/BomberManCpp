#include "CollisionManager.hpp"
#include "Enemy.hpp"
#include <algorithm>
#include <queue>
#include <set>

enum
{
    GRASS = 2,
};

typedef std::pair<int, int> Position;

Enemy::Enemy() : mSpeed(3), mBombTickingTime(3), mBombPosition(), mExplosion(false), mBombReady(true), mMoving(false),
                 mNow(SDL_GetTicks()) ,mTimer(SDL_GetTicks())
{}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    mNow = SDL_GetTicks();

    handleMovement();
    handleBomb();
    handleAnimation();
}

void Enemy::clean()
{}

void Enemy::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
}

void Enemy::handleMovement()
{
    int enemyY = mPosition.getX() / TheCollisionManager::Instance()->getTileWidth();
    int enemyX = mPosition.getY() / TheCollisionManager::Instance()->getTileHeight();

    Position playerPos = TheCollisionManager::Instance()->getPlayerPosition();
    Position enemyPos(enemyX, enemyY);
    std::vector<std::vector<int>> mapMatrix = TheCollisionManager::Instance()->getMap();

    std::queue<Position> queue;
    std::vector<std::vector<Position>> parent(mapMatrix.size(), std::vector<Position>(mapMatrix[0].size(), {-1, -1}));

    queue.push(enemyPos);

    while (!queue.empty())
    {
        Position currentPos = queue.front();
        queue.pop();

        if (currentPos == playerPos) {
            // Shortest path found
            break;
        }

        std::vector<std::pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (const auto& direction : directions) {
            Position nextPos = std::make_pair(currentPos.first + direction.first, currentPos.second + direction.second);

            if (nextPos.first >= 0 && nextPos.first < int(mapMatrix.size()) &&
                nextPos.second >= 0 && nextPos.second < int(mapMatrix[0].size()) &&
                mapMatrix[nextPos.first][nextPos.second] == GRASS &&
                parent[nextPos.first][nextPos.second] == std::make_pair(-1, -1)) {

                queue.push(nextPos);
                parent[nextPos.first][nextPos.second] = currentPos;
            }
        }
    }

    // Determine next move based on the parent positions
    Position currentPos = playerPos;
    while (parent[currentPos.first][currentPos.second] != enemyPos) {
        currentPos = parent[currentPos.first][currentPos.second];
        if(currentPos == std::make_pair(-1,-1))
            break;
    }

    if(abs(enemyPos.first - playerPos.first) < 1 && abs(enemyPos.second - playerPos.second) < 1)
        placeBomb();

    move(enemyPos, currentPos);
}

void Enemy::handleAnimation()
{
    if(mMoving)
        mCurrentFrame = int(((SDL_GetTicks() / 200) % mNumFrames));
    else
        mCurrentFrame = 1;
}

void Enemy::move(std::pair<int,int> pEnemyPos, std::pair<int,int> pNextPos)
{
    if(pEnemyPos.first + 1 == pNextPos.first) // Move Down
    {
        Vector2D newPos1(mPosition.getX(), mPosition.getY() + mSpeed + mHeight);
        Vector2D newPos2(mPosition.getX() + mWidth, mPosition.getY() + mSpeed + mHeight);

        if(TheCollisionManager::Instance()->tileCollisionEnemy(newPos1)
           || TheCollisionManager::Instance()->tileCollisionEnemy(newPos2))
        {
            mCurrentRow = LEFT_MOVEMENT;
            newPos1.setX(newPos1.getX() - 3);
            newPos1.setY(mPosition.getY());
            mPosition = newPos1;
        }
        else
        {
            mCurrentRow = DOWN_MOVEMENT;
            newPos1.setY(newPos1.getY() - mHeight);
            mPosition = newPos1;
        }
        mMoving = true;
    }
    else if(pEnemyPos.first - 1 == pNextPos.first) // Move Up
    {
        Vector2D newPos1(mPosition.getX(), mPosition.getY() - mSpeed);
        Vector2D newPos2(mPosition.getX() + mWidth, mPosition.getY() - mSpeed);

        if(TheCollisionManager::Instance()->tileCollisionEnemy(newPos1) ||
           TheCollisionManager::Instance()->tileCollisionEnemy(newPos2))
        {
            mCurrentRow = LEFT_MOVEMENT;
            newPos1.setX(newPos1.getX() - 3);
            newPos1.setY(mPosition.getY());
            mPosition = newPos1;
        }
        else
        {
            mCurrentRow = UP_MOVEMENT;
            mPosition = newPos1;
        }
        mMoving = true;
    }
    else if(pEnemyPos.second + 1 == pNextPos.second) // Move right
    {
        Vector2D newPos1(mPosition.getX() + mWidth + mSpeed, mPosition.getY());
        Vector2D newPos2(mPosition.getX() + mWidth + mSpeed, mPosition.getY() + mHeight);

        if(TheCollisionManager::Instance()->tileCollisionEnemy(newPos1) ||
           TheCollisionManager::Instance()->tileCollisionEnemy(newPos2))
        {
            mCurrentRow = UP_MOVEMENT;
            newPos1.setX(mPosition.getX());
            newPos1.setY(newPos1.getY() - 3);
            mPosition = newPos1;
        }
        else
        {
            mCurrentRow = RIGHT_MOVEMENT;
            newPos1.setX(newPos1.getX() - mWidth);
            mPosition = newPos1;
        }
        mMoving = true;
    }
    else if(pEnemyPos.second - 1 == pNextPos.second) // Move left
    {
        Vector2D newPos1(mPosition.getX() - mSpeed, mPosition.getY());
        Vector2D newPos2(mPosition.getX() - mSpeed, mPosition.getY() + mHeight);

        if(TheCollisionManager::Instance()->tileCollisionEnemy(newPos1) ||
           TheCollisionManager::Instance()->tileCollisionEnemy(newPos2))
        {
            mCurrentRow = UP_MOVEMENT;
            newPos1.setX(mPosition.getX());
            newPos1.setY(newPos1.getY() - 3);
            mPosition = newPos1;
        }
        else
        {
            mCurrentRow = LEFT_MOVEMENT;
            mPosition = newPos1;
        }
    }
    else
        mMoving = false;
}

void Enemy::placeBomb()
{
    if(mBombReady)
    {
        mTimer = SDL_GetTicks();
        mBombPosition = mPosition;
        TheCollisionManager::Instance()->placeBomb(mPosition);
        mBombReady = false;
    }
}

void Enemy::handleBomb()
{
    if(! mBombReady && (float(mNow - mTimer)) / 1000 > mBombTickingTime)
    {
        TheCollisionManager::Instance()->explodeBomb(mBombPosition, 2);
        mTimer = SDL_GetTicks();
        mExplosion = true;
    }

    if(mExplosion && (float(mNow - mTimer)) / 1000 > 0.5)
    {
        TheCollisionManager::Instance()->afterExplosion(mBombPosition, 2);

        mExplosion = false;
        mBombReady = true;
    }
}
