#include "Game.h"
#include "Input.h"
#include "Globals.h"
#include "Ball.h"

//static variable Definition
sf::Time Game::deltaTime = sf::Time();

Game::Game()
{
    srand(unsigned int(time(NULL)));
    GameLoop();
}

void Game::GameLoop()
{
    sf::RenderWindow window(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), "Test");
    sf::Clock deltaTimer;
    Graphics graphics(&window);
    Input input;
    
    //Testing area

    sf::Vector2f startPos(Globals::SCREEN_WIDTH / 2.f, Globals::SCREEN_HEIGHT / 2.f);
    sf::Vector2f velocity(10, 45);

    Ball ball1(startPos, velocity);
    velocity *= -2.f;
    Ball ball2(startPos, velocity);
    sf::Vector2f velocity2(45, -36);

    Ball ball3(startPos, velocity2);

    
    shape.setPosition(startPos);
    shape.setRadius(2);
    shape.setOrigin(shape.getRadius(), shape.getRadius());

    while (window.isOpen())
    {
        sf::Event event;

        deltaTime = deltaTimer.restart();

        while (window.pollEvent(event))
        {           
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                //break;
            }


        }

        //float shapeSpeed = 100;
        //background.move(input.GetAxisDirection() * GetDeltaTime() * shapeSpeed);

        Update();
        ball1.Update();
        ball2.Update();
        ball3.Update();

        //Draw(&graphics);
        window.clear();
        
        window.draw(ball1.shape);
        window.draw(ball2.shape);
        window.draw(ball3.shape);

        window.draw(shape);

        window.display();

    }
}

void Game::Update()
{
}

void Game::Draw(const Graphics* graphics)
{
    
}

