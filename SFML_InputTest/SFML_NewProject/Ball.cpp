#include "Ball.h"
#include "Globals.h"

Ball::Ball(sf::Vector2f initPosition, sf::Vector2f initVelocity)
{
	
	
	shape.setFillColor(sf::Color(std::rand() % 255 + 1, std::rand() % 255 + 1, std::rand() % 255 + 1));
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2.f);
	shape.setOrigin(50, 50);
	shape.setPosition(initPosition);
	shape.setRadius(50);

	velocity = initVelocity;
}

void Ball::Update()
{
	sf::Vector2f position = shape.getPosition();
	
	if (position.y > Globals::SCREEN_HEIGHT)
	{
		velocity.y *= -1;
		shape.setPosition(position.x, Globals::SCREEN_HEIGHT);
	}
	else if (position.y < 0)
	{
		velocity.y *= -1;
		shape.setPosition(position.x, 0);
	}

	position = shape.getPosition();

	if (position.x < 0)
	{
		velocity.x *= -1;
		shape.setPosition(0 , position.y);

	}
	else if (position.x > Globals::SCREEN_WIDTH)
	{
		velocity.x *= -1;
		shape.setPosition(Globals::SCREEN_WIDTH, position.y);
	}

	shape.move(velocity * Game::GetDeltaTime());
}
