#include "Game.h"
#include "Input.h"
#include "Resources.h"

//static variable Definition
sf::Time Game::deltaTime = sf::Time();

Game::Game()
{
    //Grid Setup

    grid.resize(Globals::COLUMNS);

    for (int i = 0; i < grid.size(); i++)
    {
        grid[i].resize(Globals::ROWS);
    }
    for (int i = 0; i < Globals::COLUMNS; i++)
    {
        for (int j = 0; j < Globals::ROWS; j++)
        {
            grid[i][j].block.originOffset = sf::Vector2i(i, j);
        }
    }
    srand(unsigned int(time(NULL)));
    GameLoop();
}

void Game::Reset()
{
    //clear board
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            grid[i][j].isFilled = false;
            grid[i][j].block.sprite.setTexture(resources.emptyBlockTexture);
        }
    }

    if (pCurrentPiece)
    {
        delete pCurrentPiece;
        pCurrentPiece = NULL;
    }

    if (pHoldPiece)
    {
        delete pHoldPiece;
        pHoldPiece = NULL;
    }

    if (!pieceQueue.empty())
    {
        pieceQueue.clear();
    }

    for (size_t i = 0; i < pieceQueueInitSize; i++)
    {
        Tetramino* temp = new Tetramino(resources, &grid);
        temp->origin = nextPos;
        for (size_t i = 0; i < (rand() % 4); i++)
        {
            temp->RotateClockwise();
        }
        pieceQueue.push_back(std::unique_ptr<Tetramino>(temp));
    }

    pCurrentPiece = new Tetramino(resources, &grid);
    pCurrentPiece->origin = startPos;
}

Tetramino* Game::GetFromQueue()
{
    if (!pieceQueue.empty())
    {
        Tetramino* temp = pieceQueue.front().release();
        temp->origin = startPos;
        pieceQueue.pop_front();
        pieceQueue.push_back(std::unique_ptr<Tetramino>(new Tetramino(resources, &grid)));
        pieceQueue.back().get()->origin = nextPos;

        return temp;
    }

    return nullptr;
}

void Game::ClearRow(int row)
{
    for (int i = 0; i < Globals::COLUMNS; i++)
    {
        grid[i][row].isFilled = false;
        grid[i][row].block.sprite.setTexture(resources.emptyBlockTexture);

    }
    //moveSound rows down

    for (int i = row - 1; i >= 0; i--)
    {
        for (int j = 0; j < Globals::COLUMNS; j++)
        {
            grid[j][i + 1].isFilled = grid[j][i].isFilled;
            grid[j][i + 1].block.sprite.setTexture(*grid[j][i].block.sprite.getTexture());

        }
    }
}

void Game::CheckForRows()
{
    int rowCount = 0;
    for (int i = 0; i < Globals::ROWS; i++)
    {
        bool canClear = true;
        for (int j = 0; j < Globals::COLUMNS; j++)
        {
            if (!grid[j][i].isFilled)
            {
                canClear = false;
                break;
            }
        }

        if (canClear)
        {
            ClearRow(i);
            rowCount++;
        }

    }

    if (rowCount > 3)
    {
        audioManager.Play(AudioManager::audioClips::fourClear);
    }
    else if (rowCount > 0)
    {
        audioManager.Play(AudioManager::audioClips::clear);

    }
}

void Game::DropCurrentPiece()
{
    pCurrentPiece->SetOnGrid();

    if (pCurrentPiece)
    {
        delete pCurrentPiece;
        pCurrentPiece = NULL;
    }

    CheckForRows();
    pCurrentPiece = GetFromQueue();

    if (!pCurrentPiece->CheckValidPosition())
    {
        Reset();
    }

    canHoldPiece = false;
}

void Game::HoldAction()
{
    if (!pHoldPiece)
    {
        pHoldPiece = pCurrentPiece;
        pHoldPiece->origin = holdPos;
        pCurrentPiece = GetFromQueue();
    }
    else 
    {
        Tetramino* pTemp = pCurrentPiece;
        pCurrentPiece = pHoldPiece;
        pHoldPiece = pTemp;

        pHoldPiece->origin = holdPos;
        pCurrentPiece->origin = startPos;
    }

    audioManager.Play(AudioManager::audioClips::hold);
}

void Game::GameLoop()
{
    sf::RenderWindow window(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), "Tetris");
    sf::View view(sf::Vector2f(Globals::SCREEN_WIDTH / 2.f, Globals::SCREEN_HEIGHT / 2.f), sf::Vector2f(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT));
    window.setView(view);
    sf::Clock deltaTimer;
    sf::Clock frameTimer;

    Reset();
    
    while (window.isOpen())
    {
        //TODO: Clean up when closing the program
        input.ReadInput(&window);

        Update();

        this->Draw(&window);
        deltaTime = deltaTimer.restart();
    }
}

void Game::Update()
{
    if (!pCurrentPiece)
    {
        return;
    }

    //input bindings
    sf::Vector2i dir (input.GetAxisDirection());
    if (input.GetKeyDown(sf::Keyboard::Left))
    {
        pCurrentPiece->Move(dir);
        audioManager.Play(AudioManager::audioClips::move);
    }

    if (input.GetKeyDown(sf::Keyboard::Right))
    {
        pCurrentPiece->Move(dir);
        audioManager.Play(AudioManager::audioClips::move);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (moveRepeatTimer > moveRepeatTime)
        {
            pCurrentPiece->Move(dir);
            audioManager.Play(AudioManager::audioClips::move);
            moveRepeatTimer = 0;
        }
        moveRepeatTimer += deltaTime.asSeconds();
    }
    else
    {
        moveRepeatTimer = 0;
    }

    if (input.GetKeyDown(sf::Keyboard::Up))
    {
        audioManager.Play(AudioManager::audioClips::rotate);
        pCurrentPiece->TryRotate(Globals::CLOCKWISE);
    }

    if (input.GetKeyDown(sf::Keyboard::RShift))
    {
        audioManager.Play(AudioManager::audioClips::rotate);
        pCurrentPiece->TryRotate(Globals::COUNTERCLOCKWISE);
    }

    if (input.GetKeyDown(sf::Keyboard::Down))
    {
        pCurrentPiece->HardDrop();
        graceTimer = graceTime + 1;
        audioManager.Play(AudioManager::audioClips::drop);

    }

    if (input.GetKeyDown(sf::Keyboard::Space))
    {
        if (!canHoldPiece)
        {
            HoldAction();
            canHoldPiece = true;
        }

    }

    //fall section
    if (dropCounter > dropTime)
    {
        if (!pCurrentPiece->Move(sf::Vector2i(0, 1)))
        {
            if (graceTimer > graceTime)
            {
                DropCurrentPiece();
            }
        }
        else
        {
            graceTimer = 0;
        }

        dropCounter = 0;
    }
    graceTimer += deltaTime.asSeconds();
    dropCounter += deltaTime.asSeconds();
}

void Game::Draw(sf::RenderWindow* window)
{
    window->clear();

    int xOffset = 10;
    int yOffset = -2;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            grid[i][j].block.Draw(window, sf::Vector2i(xOffset, yOffset));
        }
    }

    if (pCurrentPiece)
    {
        pCurrentPiece->Draw(window, sf::Vector2i(xOffset, yOffset));
    }

    if (pHoldPiece)
    {
        pHoldPiece->Draw(window, sf::Vector2i(xOffset, 0));
    }

    if (!pieceQueue.empty())
    {   
        int i = 0;
        for (std::list<std::unique_ptr<Tetramino>>::iterator it = pieceQueue.begin(); it != pieceQueue.end(); ++it)
        {         
            it->get()->Draw(window, sf::Vector2i(xOffset, i * 5));
            i++;
        }
    }
    window->display();
}


