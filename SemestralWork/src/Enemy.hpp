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

private:
    /**
     * This method implements a simple enemy AI
     */
    void handleMovement();

    float mSpeed;
    float mBuffer;
    bool mMoveUp;
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
