#pragma once
#include "../LoaderParams.hpp"
#include "../Levels/TileLayer.hpp"
#include <vector>

/**
 * @class GameObject
 * This is a base class for all of the game object of the game
 */
class GameObject
{
public:
    /**
     * This method is responsible for rendering the GameObject
     */
    virtual void draw() = 0;

    /**
     * This method is responsible for updating the GameObject
     */
    virtual void update() = 0;

    /**
     * This method is responsible for cleaning after the GameObject
     */
    virtual void clean() = 0;

    /**
     * This method is responsible for loading up the GameObject
     * @param pParams
     */
    virtual void load(const LoaderParams* pParams) = 0;

protected:
    GameObject();
    virtual ~GameObject();
};
