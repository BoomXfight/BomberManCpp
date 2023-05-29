#pragma once
#include <string>
#include <map>
#include "../GameObjects/GameObject.hpp"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator();

};

class GameObjectFactory
{
public:
    static GameObjectFactory* Instance();
    bool registerType(std::string typeID, BaseCreator *pCreator);
    GameObject *create(std::string typeID);

private:
    GameObjectFactory();
    ~GameObjectFactory();

    static GameObjectFactory* s_pInstance;
    std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;
