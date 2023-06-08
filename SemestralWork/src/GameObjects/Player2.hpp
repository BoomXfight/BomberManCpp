#pragma once
#include "Player.hpp"
#include "../Singletons/GameObjectFactory.hpp"

class Player2 : public Player
{
public:
    Player2();
    void handleInput();

    enum
    {
        RIGHT_MOVEMENT = 3,
        LEFT_MOVEMENT = 4,
        UP_MOVEMENT = 2,
        DOWN_MOVEMENT = 1
    };
};

class Player2Creator : public BaseCreator
{
    GameObject* createGameObject() const {return new Player2();}
};
