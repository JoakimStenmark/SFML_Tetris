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

void Input::ReadInput(sf::RenderWindow* window)
{
    sf::Event event;
    frameLeft = false;
    frameRight = false;
    frameUp = false;
    frameDown = false;
    
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
            printf("window closed");
            return;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window->close();
                printf("window closed by escape");
                return;
            }

            if (!inputLeft)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    frameLeft = true;
                    inputLeft = true;
                }
            }

            if (!inputRight)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    frameRight = true;
                    inputRight = true;
                }
            }

            if (!inputDown)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    frameDown = true;
                    inputDown = true;
                }

            }

            if (!inputUp)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    frameUp = true;
                    inputUp = true;
                }

            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                inputLeft = false;
            }

            if (event.key.code == sf::Keyboard::Right)
            {
                inputRight = false;
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                inputDown = false;
            }

            if (event.key.code == sf::Keyboard::Up)
            {
                inputUp = false;
            }
        }
    }
}

bool Input::GetKeyDown(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        return frameLeft;
        break;
    case sf::Keyboard::Right:
        return frameRight;
        break;
    case sf::Keyboard::Up:
        return frameUp;
        break;
    case sf::Keyboard::Down:
        return frameDown;
        break;
    default: printf("Input not Bound");
        break;
    }
    return false;
}
