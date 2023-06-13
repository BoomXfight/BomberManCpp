#pragma once
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "GameObject.hpp"

/**
 * @class SDLGameObject
 * This class is base class for all the other GameObject of the game
 */
class SDLGameObject : public GameObject
{
public:
    SDLGameObject();

    /**
     * This method is responsible for rendering the SDLGameObject to the screen
     */
    void draw() override;

    /**
     * This method is responsible for updating the SDLGameObject
     */
    void update() override;

    /**
     * This method is responsible for cleaning after the SDLGameObject if it contains something to be cleaned
     */
    void clean() override;

    /**
     * This method loads the SDLGameObject
     * @param[in] pParams loading parameters
     */
    void load(const LoaderParams *pParams) override;

    int getWidth() const {return mWidth;};
    int getHeight() const {return mHeight;};
    Vector2D getPosition() {return mPosition;};

protected:
    Vector2D mPosition;
    Vector2D mVelocity;
    Vector2D mAcceleration;

    int mWidth;
    int mHeight;
    int mCurrentRow;
    int mCurrentFrame;
    int mNumFrames;
    std::string mTextureID;
};
