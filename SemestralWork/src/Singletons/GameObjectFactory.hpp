#pragma once
#include <string>
#include <map>
#include "../GameObjects/GameObject.hpp"

/**
 * @class BaseCreator
 * This is a base class for every GameObjectCreator class
 * It is responsible for dynamically creating GameObjects
 */
class BaseCreator
{
public:
    /**
     * This method will create GameObject.
     * @return GameObject
     */
    virtual GameObject* createGameObject() const = 0;

    virtual ~BaseCreator();
};

/**
 * @class GameObjectFactory
 * This singleton class is responsible for storing the known GameObject creators and registering new ones
 */
class GameObjectFactory
{
public:
    static GameObjectFactory* Instance();

    /**
     * This method registers a new type that is suitable for creation -> has a creator method
     * @param[in] typeID
     * @param[in] pCreator
     * @return ture -> successfully registered, false -> already registered
     */
    bool registerType(const std::string& pTypeID, BaseCreator *pCreator);

    /**
     * This method creates an object (if registered) specified by an id
     * @param[in] typeID
     * @return nullptr -> failed to create a desired object, GameObject* -> successful creation
     */
    GameObject *create(const std::string& pTypeID);

private:
    GameObjectFactory();

    ~GameObjectFactory();

    static GameObjectFactory* mInstance;
    std::map<std::string, BaseCreator*> mCreators;
};

typedef GameObjectFactory TheGameObjectFactory;
