#pragma once
#include <vector>
#include <list>
#include <deque>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Tetramino.h"
#include "Input.h"
#include "Globals.h"
#include "AudioManager.h"

class Game
{
public:
	Game();
	~Game();
	void CleanUp();
	static float GetDeltaTime() { return deltaTime.asSeconds(); };
private:

	Resources resources;
	Input input;
	AudioManager audioManager;
	
	static sf::Time deltaTime;
	float dropTime = 0.2f;
	float dropCounter = 0;

	float graceTime = 0.3f;
	float graceTimer = 0;

	float moveRepeatTime = 0.1f;
	float moveRepeatTimer = 0;

	Tetrimino* pCurrentPiece;
	Tetrimino* pHoldPiece;

	//using unique_ptr to try it out in a list. makes clearing the list simpler.
	std::deque<std::unique_ptr<Tetrimino>> pieceQueue;
	int pieceQueueInitSize = 4;

	sf::Vector2i startPos { Globals::COLUMNS / 2, 1 };
	sf::Vector2i holdPos { -3, 3 };
	sf::Vector2i nextPos { Globals::COLUMNS + 3, 3 };

	bool canHoldPiece = false;

	//Holds blocks when tetraminos settle. Doesn't reference created blocks, only gets their texture.
	std::vector<std::vector<GridCell>> grid;
	
	void Reset();
	
	Tetrimino* GetFromQueue();
	void ClearRow(int row);
	void CheckForRows();
	void DropCurrentPiece();
	void HoldAction();
	
	void GameLoop();
	void Update();
	void Draw(sf::RenderWindow* window);
};


