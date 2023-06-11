#pragma once
#include "SDLGameObject.hpp"
#include "../Singletons/GameObjectFactory.hpp"

/**
 * @class StaticObject
 * This class is responsible for all of the static objects throughout the game. Use it for pictures or static texts.
 */
class StaticObject : public SDLGameObject
{
public:
    StaticObject();

    /**
     * This method is responsible for updating the StaticObject
     */
    void update() override;
};

/**
 * @class StaticObjectCreator
 * This class is responsible for the creation of StaticObject
 */
class StaticObjectCreator : public BaseCreator
{
    /**
     * This method creates a new StaticObject
     * @return Enemy object
     */
    GameObject* createGameObject() const override {return new StaticObject();}
};
