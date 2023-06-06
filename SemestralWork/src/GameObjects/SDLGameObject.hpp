#pragma once
#include "../Singletons/TextureManager.hpp"
#include "GameObject.hpp"
#include "../Vector2D.hpp"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject();
    void draw() override;
    void update() override;
    void clean() override;
    void load(const LoaderParams *pParams) override;
    int getWidth() {return mWidth;};
    int getHeight() {return mHeight;};
    Vector2D getPosition() {return mPosition;};
    Vector2D getVelocity() {return mVelocity;};

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