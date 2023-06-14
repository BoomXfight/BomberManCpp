#pragma once
#include "Player1.hpp"
#include "Vector2D.hpp"
#include "TileLayer.hpp"
#include "ObjectLayer.hpp"
#include "Level.hpp"
#include <vector>

enum
{
    HARD = 1,
    FREE = 2,
    BREAKABLE = 3,
    EXPLOSION = 4,
    BOMB = 5
};

/**
 * @class CollisionManager
 * This singleton class is responsible for collision handling between Payers, GameObjects and Map tiles.
 * This class also updates the Map tiles due to external interaction with it.
 */
class CollisionManager
{
public:
    static CollisionManager* Instance();

    void setTileLayer(TileLayer* pTileLayer);

    void setObjectLayer(ObjectLayer* pObjectLayer);

    void setBonuses(std::vector<Bonus*> pBonuses);

    std::vector<std::vector<int>> getMap();

    std::vector<Bonus*> getBonuses();

    std::pair<int, int> getPlayerPosition();

    int getTileWidth();

    int getTileHeight();

    /**
     * This method checks for the collision between player and some blocks of tile map.
     * @param pVec[in] player position.
     * @return true -> collision, false -> no collision.
     */
    bool tileCollisionPlayer(Vector2D pVec);

    /**
     * This method checks collisions of all of the enemies with the player.
     * @param pPlayer[in] Player object.
     * @return true -> collision, false -> no collision.
     */
    bool enemyCollisionPlayer(Player* pPlayer);

    /**
     * This method checks for the collisions between the enemy position and the tile map.
     * @param pVec[in] enemy position.
     * @return true -> collision, false -> no collision.
     */
    bool tileCollisionEnemy(Vector2D pVec);

    /**
     * This method checks whether player walks over explosion.
     * @param pVec[in] player position.
     * @return true -> on fire false -> out of fire.
     */
    bool isPlayerDamaged(Vector2D pVec);

    /**
     * This method checks whether enemy walks over explosion.
     * @param pVec[in] enemy position.
     * @param pWidth[in] enemy width
     * @return true -> on fire, false -> out of fire
     */
    bool isEnemyHit(Vector2D pVec, int pWidth, int pHeight);

    /**
     * This method places the bomb to the current position.
     * @param[in] vec current position.
     */
    void placeBomb(Vector2D vec);

    /**
     * This method handles the bomb explosion.
     * @param[in] pVec bomb position.
     * @param[in] pRadius radius of the explosion.
     */
    void explodeBomb(Vector2D pVec, int pRadius);

    /**
     * This method handles the destruction of walls after the explosion.
     * @param pVec bomb position.
     * @param pRadius explosion radius.
     */
    void afterExplosion(Vector2D pVec, int pRadius);

    /**
     * This method returns the number of exploded walls and resets it to 0
     * @return no. of exploded walls
     */
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
