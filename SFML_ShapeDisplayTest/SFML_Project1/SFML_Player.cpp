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
