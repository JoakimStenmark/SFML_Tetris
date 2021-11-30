#include "ExjobUtility.h"
#include <SFML/Graphics.hpp>


sf::Vector2f Normalize(const sf::Vector2f& pVector)
{
    float length = GetVector2fLength(pVector);
    if (length != 0)
    {
        return sf::Vector2f(pVector.x / length, pVector.y / length);
    }
    return pVector;
}

float GetVector2fLength(const sf::Vector2f& pVector)
{
    float length = sqrtf((pVector.x * pVector.x) + (pVector.y * pVector.y));
    return length;
}