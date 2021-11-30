#include "Game.h"
#include "Input.h"
#include "Resources.h"
#include "SFML_Player.h"

//static variable Definition
sf::Time Game::deltaTime = sf::Time();

Game::Game()
{
    srand(unsigned int(time(NULL)));
    GameLoop();
}

void Game::Reset()
{
    
}


void Game::GameLoop()
{

    sf::RenderWindow window(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), "SFML Window");
    sf::Clock deltaTimer;
    sf::Clock frameTimer;
    //Testing area
    
    while (window.isOpen())
    {
        input.ReadInput(&window);

        Update();

        this->Draw(&window);
        deltaTime = deltaTimer.restart();
    }
}

void Game::Update()
{
    
    player.Move(input.GetAxisDirection());
}

void Game::Draw(sf::RenderWindow* window)
{
    window->clear();
    //Draw calls here
    player.Draw(window);
    window->display();
}


