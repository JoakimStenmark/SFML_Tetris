#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>


class Input
{
public:
	sf::Vector2f GetAxisDirection();
	void ReadInput(sf::RenderWindow* window);
	
	//Was key pressed this frame
	bool GetKeyDown(sf::Keyboard::Key key);

	struct InputFrame
	{
		sf::Keyboard::Key key;

		//true the frame it was pressed
		bool frameKey = false;

		//true while key is held
		bool holdKey = false;
	};

private:	

	void ReadKeyPressed(sf::Keyboard::Key keyPressed, InputFrame &inputFrame);
	void ReadKeyReleased(sf::Keyboard::Key keyPressed, InputFrame &inputFrame);
	
	InputFrame left = { sf::Keyboard::Left };
	InputFrame right = { sf::Keyboard::Right };
	InputFrame down = { sf::Keyboard::Down };
	InputFrame up = { sf::Keyboard::Up };
	InputFrame space = { sf::Keyboard::Space };
	InputFrame rShift = { sf::Keyboard::RShift };

};

