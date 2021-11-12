#include "Graphics.h"
#include <SFML/Graphics.hpp>

Graphics::Graphics(sf::RenderWindow* pWindow)
{
	window = pWindow;
}

Graphics::~Graphics()
{
	window = NULL;
}

void Graphics::Draw()
{
}
