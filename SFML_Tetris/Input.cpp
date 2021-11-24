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

    left.frameKey = false;
    right.frameKey = false;
    down.frameKey = false;
    up.frameKey = false;
    space.frameKey = false;
    rShift.frameKey = false;
    p.frameKey = false;

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

            ReadKeyPressed(event.key.code, left);
            ReadKeyPressed(event.key.code, right);
            ReadKeyPressed(event.key.code, down);
            ReadKeyPressed(event.key.code, up);
            ReadKeyPressed(event.key.code, space);
            ReadKeyPressed(event.key.code, rShift);
            ReadKeyPressed(event.key.code, p);


        }

        if (event.type == sf::Event::KeyReleased)
        {
            ReadKeyReleased(event.key.code, left);
            ReadKeyReleased(event.key.code, right);
            ReadKeyReleased(event.key.code, down);
            ReadKeyReleased(event.key.code, up);
            ReadKeyReleased(event.key.code, space);
            ReadKeyReleased(event.key.code, rShift);
            ReadKeyReleased(event.key.code, p);

        }
    }
}

bool Input::GetKeyDown(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        return left.frameKey;
        break;
    case sf::Keyboard::Right:
        return right.frameKey;
        break;
    case sf::Keyboard::Up:
        return up.frameKey;
        break;
    case sf::Keyboard::Down:
        return down.frameKey;
        break;
    case sf::Keyboard::Space:
        return space.frameKey;
        break;
    case sf::Keyboard::RShift:
        return rShift.frameKey;
        break;
    case sf::Keyboard::P:
        return p.frameKey;
        break;
    default: printf("Input not Bound");
        break;
    }
    return false;
}

void Input::ReadKeyPressed(sf::Keyboard::Key keyPressed, InputFrame &inputFrame)
{
    if (inputFrame.holdKey)
    {
        return;
    }

    if (keyPressed == inputFrame.key)
    {
        inputFrame.frameKey = true;
        inputFrame.holdKey = true;
    }
}

void Input::ReadKeyReleased(sf::Keyboard::Key keyPressed, InputFrame &inputFrame)
{
    if (keyPressed == inputFrame.key)
    {
        inputFrame.holdKey = false;
        inputFrame.frameKey = false;
    }

}
