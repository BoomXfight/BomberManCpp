#pragma once
#include "Player.hpp"
#include "../Singletons/GameObjectFactory.hpp"

/**
 * @class Player1
 * This class implements a Player1 which is controlled by W,S,D,A keys.
 */
class Player1 : public Player
{
public:
    Player1();

    /**
     * This method is responsible for input handling and Player1 object movement.
     */
    void handleInput() override;

    enum
    {
        DOWN_MOVEMENT = 1,
        UP_MOVEMENT = 2,
        RIGHT_MOVEMENT = 3,
        LEFT_MOVEMENT = 4
    };
};

/**
 * @class Player1Creator
 * This class is responsible for the creation of Player1 object.
 */
class Player1Creator : public BaseCreator
{
    /**
     * This method creates a new Player1 object
     * @return Player1
     */
    GameObject* createGameObject() const override {return new Player1();}
};
