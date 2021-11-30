#include "SFML_Player.h"

SFML_Player::SFML_Player()
{
	Init();
}

void SFML_Player::Init()
{
	shape.setPosition(220, 130);
	shape.setFillColor(sf::Color::Green);
	shape.setRadius(size);
	
}

void SFML_Player::Draw(sf::RenderWindow* window)
{
	window->draw(shape);
}

void SFML_Player::Move(sf::Vector2f direction)
{
	shape.move(direction * shapeSpeed);
}
