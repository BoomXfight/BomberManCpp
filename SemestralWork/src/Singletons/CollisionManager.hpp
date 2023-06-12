#pragma once
#include "../GameObjects/Player1.hpp"
#include "../GameObjects/Vector2D.hpp"
#include "../Levels/TileLayer.hpp"
#include "../Levels/ObjectLayer.hpp"
#include "../Levels/Level.hpp"
#include <vector>

enum
{
    HARD = 1,
    FREE = 2,
    BREAKABLE = 3,
    EXPLOSION = 4,
    BOMB = 5
};

class CollisionManager
{
public:
    static CollisionManager* Instance();
    void setTileLayer(TileLayer* pTileLayer);
    void setObjectLayer(ObjectLayer* pObjectLayer);
    void setBonuses(std::vector<Bonus*> pBonuses);
    std::vector<Bonus*> getBonuses();
    bool tileCollisionPlayer(Vector2D pVec);
    bool enemyCollisionPlayer(Player* pPlayer);
    bool tileCollisionEnemy(Vector2D pVec);
    bool isPlayerDamaged(Vector2D pVec);
    bool isEnemyHit(Vector2D pVec);
    void placeBomb(Vector2D vec);
    void explodeBomb(Vector2D pVec, int pRadius);
    void afterExplosion(Vector2D pVec, int pRadius);
    int getResetExplodedWalls();

private:
    CollisionManager();
    static CollisionManager* mInstance;

    int mExplodedWalls;

    TileLayer* mTileLayer;
    TileSet mTileSet;
    std::vector<std::vector<int>> mMap;

    ObjectLayer* mObjectLayer;
    std::vector<GameObject*>* mGameObjects;

    std::vector<Bonus*> mBonuses;
};

typedef CollisionManager TheCollisionManager;
