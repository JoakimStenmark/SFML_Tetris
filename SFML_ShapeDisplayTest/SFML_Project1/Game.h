#pragma once
#include "Graphics.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

class Game
{
public:
	Game();

	static float GetDeltaTime() { return deltaTime.asSeconds(); };
private:

	static sf::Time deltaTime;
	void GameLoop();
	void Update();
	void Draw(const Graphics *graphics);
	sf::CircleShape shape;
	
	
};

