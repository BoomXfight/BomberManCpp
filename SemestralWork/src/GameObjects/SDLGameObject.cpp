#include "SDLGameObject.hpp"
#include "../Singletons/Game.hpp"

SDLGameObject::SDLGameObject() : GameObject()
{
}

/**
 * This method draws an SDLGameObject to the screen
 */
void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(mTextureID, (int)mPosition.getX(), (int)mPosition.getY(),
                                          mWidth, mHeight, mCurrentRow,
                                          mCurrentFrame,TheGame::Instance()->getRenderer());
}

/**
 * This method updates the SDLGameObject
 */
void SDLGameObject::update()
{
    mVelocity += mAcceleration;
    mPosition += mVelocity;
}

void SDLGameObject::clean() {}

/**
 * This method loads the SDLGameObject
 * @param[in] pParams
 */
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

