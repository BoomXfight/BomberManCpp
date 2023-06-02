#include "GameObjectFactory.hpp"
#include <iostream>

BaseCreator::~BaseCreator() {};

GameObjectFactory* GameObjectFactory::Instance()
{
    if(mInstance == nullptr)
       mInstance = new GameObjectFactory();

    return mInstance;
}

/**
 * This method registers a new type that is suitable for creation -> has a creator method
 * @param[in] typeID
 * @param[in] pCreator
 * @return ture -> successfully registered, false -> already registered
 */
bool GameObjectFactory::registerType(const std::string& pTypeID, BaseCreator *pCreator)
{
    auto it = mCreators.find(pTypeID);
    if(it != mCreators.end()) // Already registered
    {
        delete pCreator;
        return false;
    }

    mCreators[pTypeID] = pCreator;
    return true;
}

/**
 * This method creates an object (if registered) specified by an id
 * @param[in] typeID
 * @return nullptr -> failed to create a desired object, GameObject* -> successful creation
 */
GameObject* GameObjectFactory::create(const std::string& pTypeID)
{
    auto it = mCreators.find(pTypeID);
    if(it == mCreators.end())
    {
        std::cout << "could not find type: " << pTypeID << std::endl;
        return nullptr;
    }
    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}

GameObjectFactory::GameObjectFactory() {}

GameObjectFactory::~GameObjectFactory() {}

GameObjectFactory* GameObjectFactory::mInstance = nullptr;
