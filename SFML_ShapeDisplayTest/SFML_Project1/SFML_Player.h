#pragma once
#include <SFML/Graphics.hpp>


class SFML_Player
{
public:
    SFML_Player();
    void SetSize(float value);
    void Init();
    void Update();

private:
    sf::CircleShape shape;
    float size = 10;
    float shapeSpeed = 100.f;


};

