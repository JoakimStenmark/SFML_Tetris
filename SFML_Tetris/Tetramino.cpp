#include "Tetramino.h"

int Tetrimino::instanceCount = 0;

Block::Block()
{
	sprite.setScale(sf::Vector2f(Globals::SPRITE_SCALE, Globals::SPRITE_SCALE));
}

Block::Block(Resources& resources)
{
	sprite.setTexture(resources.blockTexture5);
	sprite.setScale(sf::Vector2f(Globals::SPRITE_SCALE, Globals::SPRITE_SCALE));
}

void Block::Draw(sf::RenderWindow* window, const sf::Vector2i& origin)
{
	if (sprite.getTexture())
	{
		float pixelLength = sprite.getTexture()->getSize().x * Globals::SPRITE_SCALE;
		sf::Vector2f position = sf::Vector2f(origin.x + originOffset.x,
											origin.y + originOffset.y) 
											* pixelLength;
		sprite.setPosition(position);
		window->draw(sprite);
	}
}

Tetrimino::~Tetrimino()
{
	instanceCount--;
	printf("Tetramino Destroyed. Instances : %i \n ", instanceCount);
}

Tetrimino::Tetrimino(Resources& resources, std::vector<std::vector<GridCell>>* grid)
{
	instanceCount++;
	printf("Tetramino Created. Instances : %i \n ", instanceCount);

	switch (type)
	{
		case TetriminoType::TBLOCK:
			//T-Block
			blocks[1].originOffset = { 0, 1 };
			blocks[2].originOffset = { 1, 0 };
			blocks[3].originOffset = { -1, 0 };
			break;
		case TetriminoType::JBLOCK:
			//J-Block
			blocks[1].originOffset = { 1, 0 };
			blocks[2].originOffset = { -1, 0 };
			blocks[3].originOffset = { 1, 1 };
			break;
		case TetriminoType::LBLOCK:
			//L-Block
			blocks[1].originOffset = { 1, 0 };
			blocks[2].originOffset = { -1, 0 };
			blocks[3].originOffset = { 1, -1 };
			break;
		case TetriminoType::ZBLOCK:
			//Z-Block
			blocks[1].originOffset = { -1, 0 };
			blocks[2].originOffset = { 0, 1 };
			blocks[3].originOffset = { 1, 1 };
			break;
		case TetriminoType::SBLOCK:
			//S-Block
			blocks[1].originOffset = { 1, 0 };
			blocks[2].originOffset = { 0, 1 };
			blocks[3].originOffset = { -1, 1 };
			break;
		case TetriminoType::OBLOCK:
			//O-Block
			blocks[1].originOffset = { 1, 0 };
			blocks[2].originOffset = { 0, 1 };
			blocks[3].originOffset = { 1, 1 };
			break;
		case TetriminoType::LINEPIECE:
			//LINEPIECE
			blocks[1].originOffset = { 0, -1 };
			blocks[2].originOffset = { 0, 1 };
			blocks[3].originOffset = { 0, 2 };
			break;
		default:
			break;
	}

	for(Block& b : blocks)
	{
		switch (type)
		{
		case TetriminoType::TBLOCK:
			b.sprite.setTexture(resources.blockTexture1);
			break;
		case TetriminoType::JBLOCK:
			b.sprite.setTexture(resources.blockTexture2);
			break;
		case TetriminoType::LBLOCK:
			b.sprite.setTexture(resources.blockTexture3);
			break;
		case TetriminoType::ZBLOCK:
			b.sprite.setTexture(resources.blockTexture4);
			break;
		case TetriminoType::SBLOCK:
			b.sprite.setTexture(resources.blockTexture5);
			break;
		case TetriminoType::OBLOCK:
			b.sprite.setTexture(resources.blockTexture6);
			break;
		case TetriminoType::LINEPIECE:
			b.sprite.setTexture(resources.blockTexture7);
			break;
		default:
			break;
		}
	}

	pGrid = grid;

}

void Tetrimino::Draw(sf::RenderWindow* window, sf::Vector2i drawOffset)
{
	for (Block& b : blocks)
	{
		b.Draw(window, origin + drawOffset);
	}
}

bool Tetrimino::Move(sf::Vector2i direction)
{
	origin += sf::Vector2i(direction.x, direction.y);
	if (!IsValidPosition())
	{
		origin -= sf::Vector2i(direction.x, direction.y);
		return false;
	}
	return true;
}

bool Tetrimino::IsValidPosition()
{
	for (Block& block : blocks)
	{
		sf::Vector2i blockPos = origin + block.originOffset;

		if (blockPos.x < 0)
		{
			return false;
		}

		if (blockPos.x >= Globals::COLUMNS)
		{
			return false;
		}

		if (blockPos.y >= Globals::ROWS)
		{
			return false;
		}

 		if (blockPos.y < 0)
		{
			return false;
		}
		else
		{
			GridCell& cell = (*pGrid)[(int)blockPos.x][(int)blockPos.y];
			if (cell.isFilled)
			{
				return false;
			}
		}

	}
	return true;
}

void Tetrimino::SetOnGrid()
{
	for (Block& block : blocks)
	{
		GridCell& cell = (*pGrid)[(long long)origin.x + block.originOffset.x][(long long)origin.y + block.originOffset.y];
		cell.block.sprite.setTexture(*block.sprite.getTexture());
		cell.isFilled = true;
	}
}

void Tetrimino::RotateClockwise()
{
	for (Block& block : blocks)
	{
		block.originOffset = sf::Vector2i(-block.originOffset.y, block.originOffset.x);
	}
}

void Tetrimino::RotateCounterClockwise()
{
	for (Block& block : blocks)
	{
		block.originOffset = sf::Vector2i(block.originOffset.y, -block.originOffset.x);
	}

}

void Tetrimino::TryRotate(Globals::ROTATION_DIRECTION dir)
{
	if (type == TetriminoType::OBLOCK)
	{
		return;
	}

	if (dir == Globals::CLOCKWISE)
	{
		RotateClockwise();
		if (IsValidPosition())
		{
			return;
		}

		if (Move(sf::Vector2i(1,0)))
		{
			return;
		}

		if (Move(sf::Vector2i(-1, 0)))
		{
			return;
		}

		if (Move(sf::Vector2i(-2, 0)))
		{
			return;
		}
		
		RotateCounterClockwise();
	}
	else
	{
		RotateCounterClockwise();

		if (IsValidPosition())
		{
			return;
		}

		if (Move(sf::Vector2i(1, 0)))
		{
			return;
		}

		if (Move(sf::Vector2i(-1, 0)))
		{
			return;
		}

		if (Move(sf::Vector2i(2, 0)))
		{
			return;
		}

		RotateClockwise();
	}
}

void Tetrimino::HardDrop()
{
	for (size_t i = 0; i < Globals::ROWS; i++)
	{
		if (!Move(sf::Vector2i(0, 1)))
		{
			break;
		}
	}
}


