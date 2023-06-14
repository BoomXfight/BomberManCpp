#pragma once
#include "GameObjectFactory.hpp"
#include "SDLGameObject.hpp"

/**
 * @class Enemy
 * This is class is responsible for Enemy GameObject. It represents an enemy NPC.
 */
class Enemy : public SDLGameObject {
public:
    Enemy();

    /**
     * This method is responsible for rendering the Enemy to the screen
     */
    void draw() override;

    /**
     * This method is responsible for updating the Enemy
     */
    void update() override;

    /**
     * This method cleans up after the Enemy object
     */
    void clean() override;

    /**
     * This method is used to load up Enemy object
     * @param[in] pParams loading parameters
     */
    void load(const LoaderParams *pParams) override;

    enum
    {
        DOWN_MOVEMENT = 1,
        UP_MOVEMENT = 2,
        RIGHT_MOVEMENT = 3,
        LEFT_MOVEMENT = 4
    };

private:
    /**
     * This method implements a simple enemy AI
     */
    void handleMovement();
    void handleAnimation();
    void move(std::pair<int,int> pEnemyPos, std::pair<int,int> pNextPos);
    void placeBomb();
    void handleBomb();

    float mSpeed;
    float mBombTickingTime;
    Vector2D mBombPosition;

    bool mExplosion;
    bool mBombReady;
    bool mMoving;

    Uint32 mNow;
    Uint32 mTimer;
    Uint32 mBombTickingTimer;
};

/**
 * @class EnemyCreator
 * This class is responsible for creation of Enemy object
 */
class EnemyCreator : public BaseCreator
{
    /**
     * This method creates a new Enemy object
     * @return Enemy object
     */
    GameObject* createGameObject() const override {return new Enemy();};
};
