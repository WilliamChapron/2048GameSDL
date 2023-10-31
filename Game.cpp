#include "Game.h"
#include "Box.h"
#include <iostream>
#include <vector>
#include <random>
#include <string>

// Constructor -------------


Game::Game() : size_i(4)
{
    initializeBoardBoxs();
}

Game::Game(int boardSize) : size_i(boardSize), score_i(0), totalScore_i(0)
{
    initializeGame();
    std::cout << "Game Start" << std::endl;
}


// Check End ---------------


// Check win, score 2048
bool Game::check2048Win()
{
    bool win = false;

    for (int i = 0; i < size_i; ++i)
    {
        for (int j = 0; j < size_i; ++j)
        {
            if (score_i == 2048)
            {
                win = true;
            }
        }
    }
    return win;
}

// Check lose, board full
bool Game::checkBoardFull()
{
    bool full = true;

    for (int i = 0; i < size_i; ++i)
    {
        for (int j = 0; j < size_i; ++j)
        {
            if (boardNumbers[i][j] != 1)
            {
                full = false;
            }
        }
    }
    return full;
}

// Check all ends
bool Game::checkEnd()
{
    bool end = false;

    if (check2048Win())
    {
        end = true;
        cout << "Vous avez gagné 2048 !" << endl;
    }
    else if (checkBoardFull())
    {
        end = true;
        cout << "Match nul. Le tableau est plein." << endl;
    }

    return end;
}



// Init-----------------------

void Game::initializeGame()
{
    initializeBoard();
}

void Game::initializeBoardBoxs()
{
    int rows = size_i;
    int cols = size_i;

    boardNumbers.resize(rows, std::vector<int>(cols, 0));
    boardBoxs.resize(rows, std::vector<Box>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            createBox(i, j, 0); // Initialize each box with a value 0 
            //Box currentBox = boardBoxs[i][j];
            //int boxValue = currentBox.getValue();
        }
    }
}

void Game::initializeBoard()
{
    initializeBoardBoxs();

    // Init two boxes to start the game
    for (int i = 0; i < 2; ++i)
    {
        int randomI = generateRandomNumber(0, size_i - 1);
        int randomJ = generateRandomNumber(0, size_i - 1);

        createBox(randomI, randomJ, 1);
        setBoardNumbers(randomI, randomJ, 1);
    }

}

void Game::createBox(int i, int j, int value)
{
    boardBoxs[i][j] = Box(i, j, score_i, value);
}



// Tools--------------------------


void Game::spawnRandomBox()
{
    std::vector<std::string> emptyBoxs;

    for (int i = 0; i < size_i; ++i)
    {
        for (int j = 0; j < size_i; ++j)
        {
            if (boardNumbers[i][j] == 0)
            {
                std::string position = std::to_string(i) + std::to_string(j);
                emptyBoxs.push_back(position);
            }
        }
    }

    if (!emptyBoxs.empty())
    {
        int randomIndex = generateRandomNumber(0, emptyBoxs.size() - 1);

        int randomI = std::stoi(emptyBoxs[randomIndex].substr(0, 1));
        int randomJ = std::stoi(emptyBoxs[randomIndex].substr(1, 1));

        createBox(randomI, randomJ, 2);
        setBoardNumbers(randomI, randomJ, 1);
    }
}


int Game::generateRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}



MoveResult Game::eventMoves(int moveEvent) // Change events 1,2,3,4 from the users keys to a struct -1, 0, ...
{
    MoveResult result;

    switch (moveEvent)
    {
    case 1:
        result = { -1, 0 };
        break;
    case 2:
        result = { 1, 0 };
        break;
    case 3:
        result = { 0, -1 };
        break;
    case 4:
        result = { 0, 1 };
        break;
    }

    return result;
}


// Get ----------------------------

int Game::getSize()
{
    return size_i;
}

int Game::getScore()
{
    return score_i;
}

int Game::getTotalScore()
{
    return totalScore_i;
}

std::vector<std::vector<int>>& Game::getBoardNumbers()
{
    return boardNumbers;
}

std::vector<std::vector<Box>>& Game::getBoardBoxs()
{
    return boardBoxs;
}

std::string Game::getMessage()
{
    return moveStateMessage_s;
}


// Set ----------------------------

void Game::setBoardNumbers(int i, int j, int value) {
    boardNumbers[i][j] = value;
}




// Game Logic ---------------------


void Game::move(int moveEvent)
{
    moveState_i = 0;

    if (moveEvent == 1 || moveEvent == 3)
    {
        UpLeftCase(moveEvent);
    }
    else if (moveEvent == 2 || moveEvent == 4)
    {
        DownRightCase(moveEvent);
    }
    if (moveState_i == 1)
    {
        spawnRandomBox();
    }
}



void Game::UpLeftCase(int moveEvent)
{
    MoveResult result = eventMoves(moveEvent);
    std::string message;

    for (int i = 0; i < size_i; i++)
    {
        for (int j = 0; j < size_i; j++)
        {
            checkEvents(i, j, result.iUser, result.jUser);
        }
    }
}

void Game::DownRightCase(int moveEvent)
{
    MoveResult result = eventMoves(moveEvent);
    std::string moveStateMessage_s;

    for (int i = size_i - 1; i >= 0; i--)
    {
        for (int j = size_i - 1; j >= 0; j--)
        {
            checkEvents(i, j, result.iUser, result.jUser);
        }
    }
}

void Game::doubleBox(int currentBoxI, int currentBoxJ, int nextBoxI, int nextBoxJ)
{
    boardBoxs[currentBoxI][currentBoxJ].setValue(0);
    boardNumbers[currentBoxI][currentBoxJ] = 0;

    boardBoxs[nextBoxI][nextBoxJ].setValue(boardBoxs[nextBoxI][nextBoxJ].getValue() * 2);
}

void Game::setTotalScore(int val)
{
    totalScore_i += val;
}


// Check Bool ------------------------


void Game::checkEvents(int i, int j, int iUser, int jUser)
{

    if (checkBoxExist(i, j))
    {
        if (not checkBorderCollide(i, j, iUser, jUser))
        {
            if (not checkBoxCollide(i, j, iUser, jUser))
            {
                // Set future position
                boardBoxs[i + iUser][j + jUser].setValue(boardBoxs[i][j].getValue());
                boardNumbers[i + iUser][j + jUser] = 1;

                // Set old position
                boardBoxs[i][j].setValue(0);
                setBoardNumbers(i, j, 0);
                moveState_i = 1;
                checkEvents(i + iUser, j + jUser, iUser, jUser);
                moveStateMessage_s += "no box collision/";

            }
            else
            {
                moveStateMessage_s += "box collision and no fusion/";
                //std::cout << "box collide" << std::endl;
                if (checkIsDouble(i, j, iUser, jUser))
                {
                    moveState_i = 1;
                    //std::cout << "double !!!" << std::endl;
                    doubleBox(i, j, i + iUser, j + jUser);
                    setTotalScore(boardBoxs[i + iUser][j + jUser].getValue());
                    actualizeMaxScore(i + iUser, j + jUser);
                    moveStateMessage_s += "box collision and fusion/";

                }
            }
        }
        else
        {
            moveStateMessage_s += "border collision/";
        }
    }
}

// check if any box doubled is the new maximal score of the grid
void Game::actualizeMaxScore(int i, int j)
{
    if (score_i < boardBoxs[i][j].getValue())
    {
        score_i = boardBoxs[i][j].getValue();
        /*cout << "Votre score maximal est de :" << score_i << endl;*/
    }
}

bool Game::checkBorderCollide(int i, int j, int iUser, int jUser)
{
    if (i + iUser > size_i - 1 || j + jUser > size_i - 1 || i + iUser < 0 || j + jUser < 0)
    {
        return true;
    }
    return false;
}


bool Game::checkBoxCollide(int i, int j, int iUser, int jUser)
{
    if (boardNumbers[i + iUser][j + jUser] == 1)
    {
        return true;
    }
    return false;
}


bool Game::checkBoxExist(int i, int j)
{
    if (boardNumbers[i][j] != 0)
    {
        /*std::cout << boardNumbers[i][j] << std::endl;*/

        return true;
    }
    return false;
}


bool Game::checkIsDouble(int i, int j, int iUser, int jUser)
{
    if (checkBoxExist(i + iUser, j + jUser))
    {
        if (boardBoxs[i + iUser][j + jUser].getValue() == boardBoxs[i][j].getValue())
        {
            return true;
        }
    }
    return false;
}
