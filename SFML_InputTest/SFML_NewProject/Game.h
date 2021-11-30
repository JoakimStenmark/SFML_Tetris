#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Input.h"
#include "Globals.h"
#include "Resources.h"
#include "SFML_Player.h"

class Game
{
public:
	Game();
	static float GetDeltaTime() { return deltaTime.asSeconds(); };
private:

	static sf::Time deltaTime;
	Input input;	
	Resources resources;
	void Reset();
	SFML_Player player;
	void GameLoop();
	void Update();
	void Draw(sf::RenderWindow* window);
};


