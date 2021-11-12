#pragma once
#include <SFML/Graphics.hpp>


class SFML_Player
{
    SFML_Player();

public:
    void SetSize(float value);
    void Init();
    void Update();
    sf::Vector2f GetInputAxisDirection();

private:
    sf::CircleShape shape;
    float size;
    float shapeSpeed = 100.f;


};

