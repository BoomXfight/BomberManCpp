#pragma once
#include "../GameObjects/Player.hpp"
#include "../Levels/TileLayer.hpp"
#include "../Levels/ObjectLayer.hpp"
#include "../Levels/Level.hpp"
#include "../Vector2D.hpp"
#include <vector>

class CollisionManager
{
public:
    static CollisionManager* Instance();
    void setTileLayer(TileLayer* pObjectLayer);
    void setObjectLayer(ObjectLayer* pObjectLayer);
    bool tileCollision(Vector2D vec);
    void placeBomb(Vector2D vec);
    void explodeBomb(Vector2D pVec, int pRadius);
    void afterExplosion(Vector2D pVec, int pRadius);

private:
    CollisionManager();
    static CollisionManager* mInstance;

    TileLayer* mTileLayer;
    TileSet mTileSet;
    std::vector<std::vector<int>> mMap;

    ObjectLayer* mObjectLayer;
    std::vector<GameObject*>* mGameObjects;
};

typedef CollisionManager TheCollisionManager;
