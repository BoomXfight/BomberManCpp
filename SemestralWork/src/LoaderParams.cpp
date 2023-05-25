#include "LoaderParams.hpp"

LoaderParams::LoaderParams(int x, int y, int width, int height, std::string textureID)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID)
{}

int LoaderParams::getX() const {return m_x;}

int LoaderParams::getY() const {return m_y;}

int LoaderParams::getWidth() const {return m_width;}

int LoaderParams::getHeight() const {return m_height;}

std::string LoaderParams::getTextureID() const {return m_textureID;}
