#include "ExjobUtility.h"
#include <SFML/Graphics.hpp>


sf::Vector2f Normalize(const sf::Vector2f& sfVector)
{
    float length = GetVector2fLength(sfVector);
    if (length != 0)
    {
        return sf::Vector2f(sfVector.x / length, sfVector.y / length);
    }
    return sfVector;
}

float GetVector2fLength(const sf::Vector2f& sfVector)
{
    float length = sqrtf((sfVector.x * sfVector.x) + (sfVector.y * sfVector.y));
    return length;
}