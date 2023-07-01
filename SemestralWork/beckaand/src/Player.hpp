#pragma once
#include "SDLGameObject.hpp"

/**
 * @class Player
 * This class is responsible for Players handled by players. It handles the whole logic of Players inside the game
 * apart from the input handling.
 */
class Player : public SDLGameObject
{
public:
    Player();

    /**
     * This method updates the Player's state, how it handles bombs and bonuses and damage, lives.
     * It is the brains of the Player.
     */
    void update() override;

    int getLives() const;

    int getSpeed() const;

    int getRadius() const;

    bool isImmortal() const;

    bool fastBomb() const;

    bool isDamaged() const;

protected:
    /**
     * This method places the bomb on the Player's position if it's reloaded.
     */
    void placeBomb();

    /**
     * This method is responsible for Player's bonuses. It generates a random number and determines whether a bonus
     * should be activated.
     * @param[in] num Number that randomizes the generated number
     */
    void handleBonus(int num);

    /**
     * This method is responsible for bomb explosion as well as destruction of removable walls on the map.
     * Moreover, it determines the number of destroyed walls and gives that much opportunities for a bonus to be activated.
     */
    void handleBomb();

    /**
     * This method handles the Player lives and monitors whether the Player was caught up in an explosion.
     */
    void handleDamage();

    /**
     * This method handles the animation of the Player object, making sure that when stationary no running animation is shown.
     * On the other hand when moving, the moving animation is rendered.
     */
    void handleAnimation();

    /**
     * This method is responsible for cancelling time-based bonuses when the time of the bonus runs out.
     */
    void updateBonus();

    /**
     * This is a pure virtual method that is necessary of every Player sub-class to implement.
     */
    virtual void handleInput() = 0;

    short mRadius;
    short mSpeed;
    short mLives;
    float mBombTickingTime;
    Vector2D mBombPosition;

    bool mBombReady;
    bool mExplosion;
    bool mMoving;
    bool mImmortal;
    bool mInvisible;

    Uint32 mTimer;
    Uint32 mDamageTimer;
    Uint32 mNow;
    Uint32 mBombTickingTimer;
    Uint32 mInvisibleTimer;

    std::vector<Bonus*> mBonuses;
};
