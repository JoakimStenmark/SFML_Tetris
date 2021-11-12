#pragma once
#include <SFML/System/Vector2.hpp>
#include "Globals.h"
#include "ExjobUtility.h"
#include "Resources.h"

enum class TetraminoType
{
	TBLOCK,
	JBLOCK,
	LBLOCK,
	ZBLOCK,
	SBLOCK,
	OBLOCK,
	LINEPIECE
};

class Block
{
public:
	Block();
	Block(Resources& resources);
	sf::Vector2i originOffset;
	sf::Sprite sprite;

	void Draw(sf::RenderWindow* window, const sf::Vector2i& origin);
};

class GridCell
{
public:
	Block block;
	bool isFilled = false;
};

class Tetramino
{
public:
	Tetramino();
	~Tetramino();
	Tetramino(Resources& resources, std::vector<std::vector<GridCell>>* grid);
	sf::Vector2i origin;

	void Draw(sf::RenderWindow* window, sf::Vector2i drawOffset);
	bool Move(sf::Vector2i direction);
	bool CheckValidPosition();
	void SetOnGrid();

	void TryRotate(Globals::ROTATION_DIRECTION dir);
	void RotateClockwise();
	void RotateCounterClockwise();
	void HardDrop();
private:

	static int instanceCount;
	TetraminoType type = (TetraminoType)(rand() % 7);
	Block blocks[4];
	std::vector<std::vector<GridCell>>* pGrid;

};


