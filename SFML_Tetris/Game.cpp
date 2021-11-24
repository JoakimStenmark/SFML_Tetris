#include "Game.h"
#include "Input.h"
#include "Resources.h"

//static variable Definition
sf::Time Game::deltaTime = sf::Time();

Game::Game()
{
    holdSpace.setSize(sf::Vector2f(32 * 4, 32 * 4));
    holdSpace.setPosition(sf::Vector2f(holdPos * 32));
    holdSpace.setOrigin(32, 32 );
    holdSpace.setFillColor(sf::Color::Transparent);
    holdSpace.setOutlineThickness(10);
    holdSpace.setOutlineColor(sf::Color::White);

    queueSpace.setSize(sf::Vector2f(32 * 4, 32 * 24));
    queueSpace.setPosition(sf::Vector2f(nextPos * 32));
    queueSpace.setOrigin(64, 64);
    queueSpace.setFillColor(sf::Color::Transparent);
    queueSpace.setOutlineThickness(10);
    queueSpace.setOutlineColor(sf::Color::White);


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

    //new random seed
    srand(unsigned int(time(NULL)));
    GameLoop();
}

Game::~Game()
{
    CleanUp();
}

void Game::CleanUp()
{
    if (stats)
    {
        delete stats;
        stats = nullptr;
    }

    if (pCurrentPiece)
    {
        delete pCurrentPiece;
        pCurrentPiece = nullptr;
    }

    if (pHoldPiece)
    {
        delete pHoldPiece;
        pHoldPiece = nullptr;
    }

    if (!pieceQueue.empty())
    {
        pieceQueue.clear();
    }
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

    CleanUp();

    stats = new TetrisStats; 


    for (size_t i = 0; i < pieceQueueInitSize; i++)
    {
        pieceQueue.push_back(SpawnTetrimino());
    }

    pCurrentPiece = GetFromQueue();
}

std::unique_ptr<Tetrimino> Game::SpawnTetrimino()
{
    Tetrimino* temp = new Tetrimino(resources, &grid);
    temp->origin = nextPos;
    for (size_t i = 0; i < (rand() % 4); i++)
    {
        temp->RotateClockwise();
    }
    return std::unique_ptr<Tetrimino>(temp);
}

Tetrimino* Game::GetFromQueue()
{
    if (!pieceQueue.empty())
    {
        Tetrimino* temp = pieceQueue.front().release();
        temp->origin = startPos;
        pieceQueue.pop_front();
        pieceQueue.push_back(SpawnTetrimino());
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

    for (int i = row - 1; i >= 0; i--)
    {
        for (int j = 0; j < Globals::COLUMNS; j++)
        {
            grid[j][(long long)i + 1].isFilled = grid[j][i].isFilled;
            grid[j][(long long)i + 1].block.sprite.setTexture(*grid[j][i].block.sprite.getTexture());

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
            stats->rowsCleared++;

            if (stats->rowsCleared % stats->thresholdToSpeedUp == 0)
            {
                stats->dropTime *= 0.75f;
            }
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

    if (!pCurrentPiece->IsValidPosition())
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
        Tetrimino* pTemp = pCurrentPiece;
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
    int xOffset = (-12) * 32;
    int yOffset = 3 * 32;

    sf::View view(sf::Vector2f(Globals::SCREEN_WIDTH / 2.f + xOffset, Globals::SCREEN_HEIGHT / 2.f + yOffset), sf::Vector2f(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT));
    window.setView(view);
    sf::Clock deltaTimer;

    Reset();
    
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
    if (!pCurrentPiece)
    {
        return;
    }

    //input bindings
    sf::Vector2i dir (input.GetAxisDirection());
    if (input.GetKeyDown(sf::Keyboard::Left))
    {
        if (pCurrentPiece->Move(dir))
        {
            audioManager.Play(AudioManager::audioClips::move);
        }
    }

    if (input.GetKeyDown(sf::Keyboard::Right))
    {
        if (pCurrentPiece->Move(dir))
        {
            audioManager.Play(AudioManager::audioClips::move);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (moveRepeatTimer > stats->moveRepeatTime)
        {
            if (pCurrentPiece->Move(dir))
            {
                audioManager.Play(AudioManager::audioClips::move);
            }
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
        audioManager.Play(AudioManager::audioClips::drop);
        graceTimer = stats->graceTime + 1;
        dropCounter = stats->dropTime + 1;
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
    if (dropCounter > stats->dropTime)
    {
        if (!pCurrentPiece->Move(sf::Vector2i(0, 1)))
        {
            if (graceTimer > stats->graceTime)
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

    window->draw(holdSpace);
    window->draw(queueSpace);

    int xOffset = 0;
    int yOffset = 0;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            grid[i][j].block.Draw(window, sf::Vector2i(xOffset, yOffset));
        }
    }

    if (pCurrentPiece)
    {
        pCurrentPiece->Draw(window);
    }

    if (pHoldPiece)
    {
        pHoldPiece->Draw(window);
    }

    if (!pieceQueue.empty())
    {   
        int i = 0;
        for (std::deque<std::unique_ptr<Tetrimino>>::iterator it = pieceQueue.begin(); it != pieceQueue.end(); ++it)
        {         
            it->get()->Draw(window, sf::Vector2i(xOffset, i * 5));
            i++;
        }
    }
    window->display();
}


