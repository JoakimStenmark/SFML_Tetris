#include "Input.h"
#include "ExjobUtility.h"
#include <SFML/Window/Keyboard.hpp>

sf::Vector2f Input::GetAxisDirection()
{
    sf::Vector2f direction = sf::Vector2f(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        direction.y -= 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        direction.y += 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        direction.x -= 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        direction.x += 1.f;
    }

    direction = Normalize(direction);

    return direction;
}
