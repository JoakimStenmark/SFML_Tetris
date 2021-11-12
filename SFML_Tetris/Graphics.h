#pragma once
#include <SFML/Graphics.hpp>

class Graphics
{
	
public:
	//Graphics();

	Graphics(sf::RenderWindow *pWindow);
	~Graphics();
	sf::Time deltaTime;

private:

	sf::Clock deltaTimer;
	
	sf::RenderWindow* window;

	void Draw();

};

