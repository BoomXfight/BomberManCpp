#pragma once
#include <string>

/**
 * @class Layer
 * This is a base class for every layer in the game.
 */
class Layer
{
public:
    /**
     * This method will render the layer to the screen.
     */
    virtual void render() = 0;

    /**
     * This method will update the layer.
     */
    virtual void update() = 0;

    std::string getType() {return mType;};

protected:
    virtual ~Layer();
    std::string mType;
};
