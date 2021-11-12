#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Globals.h"
#include "ExjobUtility.h"

class Block
{
public:
	sf::Vector2i position;
	sf::Sprite sprite;

	void Draw(sf::RenderWindow* window, sf::Vector2i offset);
};



