#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>


//Graphical assets containter.
class Resources
{
public:
	Resources();
	sf::Texture blockTexture1;
	sf::Texture blockTexture2;
	sf::Texture blockTexture3;
	sf::Texture blockTexture4;
	sf::Texture blockTexture5;
	sf::Texture blockTexture6;
	sf::Texture blockTexture7;
	sf::Texture emptyBlockTexture;

	sf::Font font;
};