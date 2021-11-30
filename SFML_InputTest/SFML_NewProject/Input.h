#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>


class Input
{
public:
	sf::Vector2f GetAxisDirection();
	void ReadInput(sf::RenderWindow* window);
	bool GetKeyDown(sf::Keyboard::Key key);

private:	
	//true the frame it was pressed
	bool frameLeft = false;

	//true while key is held
	bool inputLeft = false;
	
	bool frameRight = false;
	bool inputRight = false;

	bool frameUp = false;
	bool inputUp = false;

	bool frameDown = false;
	bool inputDown = false;
};

