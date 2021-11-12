#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "Game.h"


class Ball
{

public:
	Ball(sf::Vector2f initPosition, sf::Vector2f initVelocity);
	
	void Update();
	sf::CircleShape shape;

private:
	sf::Vector2f velocity;

};

