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
    bool registerType(const std::string& pTypeID, BaseCreator *pCreator);
    GameObject *create(const std::string& pTypeID);

private:
    GameObjectFactory();
    ~GameObjectFactory();

    static GameObjectFactory* mInstance;
    std::map<std::string, BaseCreator*> mCreators;
};

typedef GameObjectFactory TheGameObjectFactory;
