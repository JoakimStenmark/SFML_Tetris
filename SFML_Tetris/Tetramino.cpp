#include "Tetramino.h"

int Tetramino::instanceCount = 0;

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

Tetramino::~Tetramino()
{
	instanceCount--;
	printf("Tetramino Destroyed. Instances : %i \n ", instanceCount);
}

Tetramino::Tetramino(Resources& resources, std::vector<std::vector<GridCell>>* grid)
{
	instanceCount++;
	printf("Tetramino Created. Instances : %i \n ", instanceCount);

	switch (type)
	{
		case TetraminoType::TBLOCK:
			//T-Block
			blocks[1].originOffset = { 0, 1 };
			blocks[2].originOffset = { 1, 0 };
			blocks[3].originOffset = { -1, 0 };
			break;
		case TetraminoType::JBLOCK:
			//J-Block
			blocks[1].originOffset = { 1, 0 };
			blocks[2].originOffset = { -1, 0 };
			blocks[3].originOffset = { 1, 1 };
			break;
		case TetraminoType::LBLOCK:
			//L-Block
			blocks[1].originOffset = { 1, 0 };
			blocks[2].originOffset = { -1, 0 };
			blocks[3].originOffset = { 1, -1 };
			break;
		case TetraminoType::ZBLOCK:
			//Z-Block
			blocks[1].originOffset = { -1, 0 };
			blocks[2].originOffset = { 0, 1 };
			blocks[3].originOffset = { 1, 1 };
			break;
		case TetraminoType::SBLOCK:
			//S-Block
			blocks[1].originOffset = { 1, 0 };
			blocks[2].originOffset = { 0, 1 };
			blocks[3].originOffset = { -1, 1 };
			break;
		case TetraminoType::OBLOCK:
			//O-Block
			blocks[1].originOffset = { 1, 0 };
			blocks[2].originOffset = { 0, 1 };
			blocks[3].originOffset = { 1, 1 };
			break;
		case TetraminoType::LINEPIECE:
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
		case TetraminoType::TBLOCK:
			b.sprite.setTexture(resources.blockTexture1);
			break;
		case TetraminoType::JBLOCK:
			b.sprite.setTexture(resources.blockTexture2);
			break;
		case TetraminoType::LBLOCK:
			b.sprite.setTexture(resources.blockTexture3);
			break;
		case TetraminoType::ZBLOCK:
			b.sprite.setTexture(resources.blockTexture4);
			break;
		case TetraminoType::SBLOCK:
			b.sprite.setTexture(resources.blockTexture5);
			break;
		case TetraminoType::OBLOCK:
			b.sprite.setTexture(resources.blockTexture6);
			break;
		case TetraminoType::LINEPIECE:
			b.sprite.setTexture(resources.blockTexture7);
			break;
		default:
			break;
		}
	}

	pGrid = grid;

}

void Tetramino::Draw(sf::RenderWindow* window, sf::Vector2i drawOffset)
{
	for (Block& b : blocks)
	{
		b.Draw(window, origin + drawOffset);
	}
}

bool Tetramino::Move(sf::Vector2i direction)
{
	origin += sf::Vector2i(direction.x, direction.y);
	if (!CheckValidPosition())
	{
		origin -= sf::Vector2i(direction.x, direction.y);
		return false;
	}
	return true;
}

bool Tetramino::CheckValidPosition()
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

void Tetramino::SetOnGrid()
{
	for (Block& block : blocks)
	{
		GridCell& cell = (*pGrid)[(int)origin.x + (int)block.originOffset.x][(int)origin.y + (int)block.originOffset.y];
		cell.block.sprite.setTexture(*block.sprite.getTexture());
		cell.isFilled = true;
	}
}

void Tetramino::RotateClockwise()
{
	for (Block& block : blocks)
	{
		block.originOffset = sf::Vector2i(-block.originOffset.y, block.originOffset.x);
	}
}

void Tetramino::RotateCounterClockwise()
{
	for (Block& block : blocks)
	{
		block.originOffset = sf::Vector2i(block.originOffset.y, -block.originOffset.x);
	}

}

void Tetramino::TryRotate(Globals::ROTATION_DIRECTION dir)
{
	if (type == TetraminoType::OBLOCK)
	{
		return;
	}

	if (dir == Globals::CLOCKWISE)
	{
		RotateClockwise();
		if (CheckValidPosition())
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

		if (CheckValidPosition())
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

void Tetramino::HardDrop()
{
	for (size_t i = 0; i < Globals::ROWS; i++)
	{
		
		if (!Move(sf::Vector2i(0, 1)))
		{
			break;
		}
	}
	
}


