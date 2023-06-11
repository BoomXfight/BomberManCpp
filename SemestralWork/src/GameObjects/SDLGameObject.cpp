#include "../Singletons/Game.hpp"
#include "SDLGameObject.hpp"

SDLGameObject::SDLGameObject() : GameObject(), mWidth(0), mHeight(0), mCurrentRow(0), mCurrentFrame(0), mNumFrames(0)
{
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(mTextureID, (int)mPosition.getX(), (int)mPosition.getY(),
                                          mWidth, mHeight, mCurrentRow,
                                          mCurrentFrame,TheGame::Instance()->getRenderer());
}

void SDLGameObject::update()
{
    mVelocity += mAcceleration;
    mPosition += mVelocity;
}

void SDLGameObject::clean() {}

void SDLGameObject::load(const LoaderParams *pParams)
{
    mPosition = Vector2D(pParams->getX(),pParams->getY());
    mWidth = pParams->getWidth();
    mHeight = pParams->getHeight();
    mTextureID = pParams->getTextureID();
    mCurrentRow = 1;
    mCurrentFrame = 1;
    mNumFrames = pParams->getNumFrames();
}
