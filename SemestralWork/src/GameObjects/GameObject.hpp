#pragma once
#include "../LoaderParams.hpp"
#include "../Levels/TileLayer.hpp"
#include <vector>


class GameObject
{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    virtual void load(const LoaderParams* pParams) = 0;

protected:
    GameObject();
    virtual ~GameObject();
};
