#include "GameObjectFactory.hpp"
#include <iostream>

BaseCreator::~BaseCreator() {}

GameObjectFactory* GameObjectFactory::Instance()
{
    if(mInstance == nullptr)
       mInstance = new GameObjectFactory();

    return mInstance;
}

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

GameObject* GameObjectFactory::create(const std::string& pTypeID)
{
    auto it = mCreators.find(pTypeID);
    if(it == mCreators.end())
    {
        std::cout << "Could not find type: " << pTypeID << "." <<std::endl;
        return nullptr;
    }
    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}

GameObjectFactory::GameObjectFactory() = default;

GameObjectFactory::~GameObjectFactory() = default;

GameObjectFactory* GameObjectFactory::mInstance = nullptr;
