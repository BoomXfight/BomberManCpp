#pragma once
#include <string>

/**
 * @class LoaderParams
 * This class is responsible for loading object of GameObjects
 * This class is used especially when manipulating with objects created by TheGameObjectFactory from a file
 */
class LoaderParams
{
public:
    LoaderParams(int x, int y, int width, int height, int frames, std::string textureID, int callbackID = 0)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_numFrames(frames), m_textureID(textureID), m_callbackID(callbackID)
    {}

    int getX() const;

    int getY() const;

    int getWidth() const;

    int getHeight() const;

    int getNumFrames() const;

    int getCallbackID() const;

    std::string getTextureID() const;

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_numFrames;
    int m_callbackID;
    std::string m_textureID;
};
