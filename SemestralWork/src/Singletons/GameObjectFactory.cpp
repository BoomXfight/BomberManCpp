#include "GameObjectFactory.hpp"
#include <iostream>

BaseCreator::~BaseCreator() {};

GameObjectFactory* GameObjectFactory::Instance()
{
    if(s_pInstance == 0)
        s_pInstance = new GameObjectFactory();

    return s_pInstance;
}

/**
 * This method registers a new type that is suitable for creation -> has a creator method
 * @param[in] typeID
 * @param[in] pCreator
 * @return ture -> successfully registered, false -> registration failed
 */
bool GameObjectFactory::registerType(std::string typeID, BaseCreator *pCreator)
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
    if(it != m_creators.end())
    {
        delete pCreator;
        return false;
    }

    m_creators[typeID] = pCreator;
    return true;
}

/**
 * This method creates an object specified by id if registered
 * @param[in] typeID
 * @return nullptr -> failed to create a desired object, GameObject* -> successful creation
 */
GameObject* GameObjectFactory::create(std::string typeID)
{
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
    if(it == m_creators.end())
    {
        std::cout << "could not find type: " << typeID << std::endl;
        return nullptr;
    }
    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}


GameObjectFactory::GameObjectFactory() {}

GameObjectFactory::~GameObjectFactory() {}

GameObjectFactory* GameObjectFactory::s_pInstance = nullptr;
