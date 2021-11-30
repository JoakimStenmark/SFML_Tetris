#pragma once
#include <SFML/Graphics.hpp>


class SFML_Player
{
public:
    SFML_Player();
    void Init();
    void Update();
    void Draw(sf::RenderWindow* window);
    void Move(sf:: Vector2f direction);

private:
    sf::CircleShape shape;
    float size = 100;
    float shapeSpeed = 1.f;

};

