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


struct TetrisConfig
{
	unsigned long long int currentScore = 0;
	const int thresholdToSpeedUp = 4;
	int rowsCleared = 0;

	float graceTime = 0.3f;
	float moveRepeatTime = 0.1f;
	float dropTime = 1.f;
	float dropTimeReduction = 0.80f;

};

class Game
{
public:
	Game();
	~Game();
	static float GetDeltaTime() { return deltaTime.asSeconds(); };
private:

	void CleanUp();
	void Reset();

	Resources resources;
	Input input;
	AudioManager audioManager;
	static sf::Time deltaTime;

	TetrisConfig* stats;

	float dropCounter = 0;
	float graceTimer = 0;
	float moveRepeatTimer = 0;

	Tetrimino* pCurrentPiece;
	Tetrimino* pHoldPiece;

	//using unique_ptr to try it out in a list. makes clearing the list simpler.
	std::deque<std::unique_ptr<Tetrimino>> pieceQueue;
	int pieceQueueInitSize = 4;

	sf::RectangleShape holdSpace;
	sf::RectangleShape queueSpace;

	sf::Vector2i startPos { Globals::COLUMNS / 2, 3 };
	sf::Vector2i holdPos { -4, 6 };
	sf::Vector2i nextPos { Globals::COLUMNS + 4, 6 };

	bool canHoldPiece = false;

	//Holds blocks when tetraminos settle. Doesn't reference created blocks, only gets their texture.
	std::vector<std::vector<GridCell>> grid;
	
	bool isPaused = false;
	sf::Text pausedText;

	std::unique_ptr<Tetrimino> SpawnTetrimino();
	
	Tetrimino* GetFromQueue();
	void ClearRow(int row);
	void CheckForRows();
	void DropCurrentPiece();
	void HoldAction();
	
	void GameLoop();
	void Update();
	void Draw(sf::RenderWindow* window);
};


