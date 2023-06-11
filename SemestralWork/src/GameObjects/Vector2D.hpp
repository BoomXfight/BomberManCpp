#pragma once
#include <cmath>
#include <string>

/**
 * @class Vector2D
 * This class is responsible for movement and positions of GameObjects.
 * It implements a mathematical 2D vector for easy manipulation with the GameObjects.
 */
class Vector2D
{
public:
    Vector2D();

    Vector2D(float x, float y);

    float getX();

    float getY();

    void setX(float x);

    void setY(float y);

    /**
     * This method calculates the length of a vector.
     * @return length.
     */
    float length();

    Vector2D operator+(const Vector2D& v2) const;

    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);

    Vector2D operator*(float scalar);

    Vector2D& operator*=(float scalar);

    Vector2D operator-(const Vector2D& v2) const;

    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

    Vector2D operator/(float scalar);

    Vector2D& operator/=(float scalar);

    /**
     * This method normalizes the vector.
     */
    void normalize();

private:
    float m_x;
    float m_y;
};
