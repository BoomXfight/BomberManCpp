#pragma once
#include "Player.hpp"
#include "../Singletons/GameObjectFactory.hpp"

/**
 * @class Player2
 * This class implements a Player2 which is controlled by arrow keys.
 */
class Player2 : public Player
{
public:
    Player2();

    /**
     * This method is responsible for input handling and Player2 object movement.
     */
    void handleInput();

    enum
    {
        DOWN_MOVEMENT = 1,
        UP_MOVEMENT = 2,
        RIGHT_MOVEMENT = 3,
        LEFT_MOVEMENT = 4
    };
};

/**
 * @class Player2Creator
 * This class is responsible for creation of Player2 object.
 */
class Player2Creator : public BaseCreator
{
    /**
     * This method creates a new Player2 object
     * @return Player2
     */
    GameObject* createGameObject() const override {return new Player2();}
};
