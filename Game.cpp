﻿#include "Game.h"
#include "Box.h"
#include <iostream>
#include <vector>
#include <random>
#include <string>

#include "DisplayManager.h"

// Constructor -------------


Game::Game() : size_i(8)
{
    initializeBoardBoxs();
}

Game::Game(int boardSize) : size_i(boardSize), score_i(2), totalScore_i(2), DisplayManagerInstance("2048", 1540, 805, boardSize, score_i, totalScore_i)
{
    initializeGame();
    std::cout << "Game Start" << std::endl;
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



    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
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

        DisplayManagerInstance.setOneCase(boardBoxs[randomI][randomJ]);
    }
}

void Game::createBox(int i, int j, int value)
{
    boardBoxs[i][j] = Box(i, j, score_i, value);
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
            if (checkNeighboor(i, j))
            {
                full = false;
            }
        }
    }
    // if full true check if double still possible
    return full;
}


//Check if the user can still DOUBLE some boxes even with board full
bool Game::checkNeighboor(int i, int j)
{
    bool neighboor = false;

    if (i == 0)
    {
        if (j == 0)
        {
            if (boardBoxs[i][j].getValue() == boardBoxs[i + 1][j].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j + 1].getValue())
            {
                neighboor = true;
            }
        }
        else if (j == size_i - 1)
        {
            if (boardBoxs[i][j].getValue() == boardBoxs[i + 1][j].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j - 1].getValue())
            {
                neighboor = true;
            }
        }
        else
        {
            if (boardBoxs[i][j].getValue() == boardBoxs[i + 1][j].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j + 1].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j - 1].getValue())
            {
                neighboor = true;
            }
        }
    }
    else if (i == size_i - 1)
    {
        if (j == 0)
        {
            if (boardBoxs[i][j].getValue() == boardBoxs[i - 1][j].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j + 1].getValue())
            {
                neighboor = true;
            }
        }
        else if (j == size_i - 1)
        {
            if (boardBoxs[i][j].getValue() == boardBoxs[i - 1][j].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j - 1].getValue())
            {
                neighboor = true;
            }
        }
        else
        {
            if (boardBoxs[i][j].getValue() == boardBoxs[i - 1][j].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j + 1].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j - 1].getValue())
            {
                neighboor = true;
            }
        }
    }
    else
    {
        if (j == 0)
        {
            if (boardBoxs[i][j].getValue() == boardBoxs[i - 1][j].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j + 1].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i + 1][j].getValue())
            {
                neighboor = true;
            }
        }
        else if (j == size_i - 1)
        {
            if (boardBoxs[i][j].getValue() == boardBoxs[i - 1][j].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j - 1].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i + 1][j].getValue())
            {
                neighboor = true;
            }
        }
        else
        {
            if (boardBoxs[i][j].getValue() == boardBoxs[i - 1][j].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j + 1].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i][j - 1].getValue() or boardBoxs[i][j].getValue() == boardBoxs[i + 1][j].getValue())
            {
                neighboor = true;
            }
        }
    }
    return neighboor;
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
        DisplayManagerInstance.setOneCase(boardBoxs[randomI][randomJ]);
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

void Game::setBoardNumbers(int i, int j, int value)
{
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
    boardNumbers[nextBoxI][nextBoxJ] = 1; // Facultatif

    // Set one case FOR display refresh
    DisplayManagerInstance.removeOneCase(boardBoxs[nextBoxI][nextBoxJ]);
    DisplayManagerInstance.setOneCase(boardBoxs[nextBoxI][nextBoxJ]);
    // Set one case FOR display refresh
    DisplayManagerInstance.removeOneCase(boardBoxs[currentBoxI][currentBoxJ]);
}

void Game::setTotalScore(int val)
{
    totalScore_i += val;
}






// Check Box anim delay

bool Game::checkBoxAnimationDelay(Box& boxObject, Uint32 currentTime)
{
    Uint32 lastExecutionTime = boxObject.getLastExecutionTime();
    Uint32 delayTime = boxObject.delayTime;

    std::cout << currentTime - lastExecutionTime << ">=?" << delayTime << std::endl;

    if (currentTime - lastExecutionTime >= delayTime)
    {
        boxObject.setLastExecutionTime(currentTime);
        return true;
    }

    return false;
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
                // Time anim synchro

                Uint32 currentTime = SDL_GetTicks();


                // Set future position
                boardBoxs[i + iUser][j + jUser].setValue(boardBoxs[i][j].getValue());
                boardNumbers[i + iUser][j + jUser] = 1;



                // Set old position
                boardBoxs[i][j].setValue(0);
                setBoardNumbers(i, j, 0);

                // Set one case FOR display refresh
                DisplayManagerInstance.removeOneCase(boardBoxs[i + iUser][j + jUser]);
                DisplayManagerInstance.setOneCase(boardBoxs[i + iUser][j + jUser]);
                DisplayManagerInstance.removeOneCase(boardBoxs[i][j]);


                moveState_i = 1;
                checkEvents(i + iUser, j + jUser, iUser, jUser);

                // checkBoxAnimationDelay attend mais il ne retente pas d'executer si l'execution n'a pas éé possible en raison du delay, car la boucle parcourt les box mais ne retente pas si les delay ne sont pas fini, il faudrait stocker dans un tableau les Box non move du fait du delay et cela empecherait de moove tant que l'anim n'est pas fini 

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




// TRY ON ANIMATION SYSTEM 

// Game Logic ---------------------


//// Check if waitAnimBoxs is empty box
//bool Game::hasNonEmptyStrings(const std::vector<std::string>& strings) {
//    for (const std::string& str : strings) {
//        if (str != "") {
//            return true; 
//        }
//    }
//    return false; 
//}


//void Game::move(int moveEvent)
//{
//    moveState_i = 0;
//
//    waitAnimBoxs.clear();
//    waitAnimBoxs.resize(size_i*size_i, "");
//
//    if (moveEvent == 1 || moveEvent == 3)
//    {
//        UpLeftCase(moveEvent);
//    }
//    else if (moveEvent == 2 || moveEvent == 4)
//    {
//        DownRightCase(moveEvent);
//    }
//
//    
//
//    if (hasNonEmptyStrings(waitAnimBoxs)) {
//        // Recursive move animation force
//        forceMoveAnimation();
//    }
//
//
//    if (moveState_i == 1)
//    {
//        spawnRandomBox();
//    }
//}

//void Game::forceMoveAnimation() {
//    for (int i = 0; i < waitAnimBoxs.size(); ++i) {
//        std::string positions = waitAnimBoxs[i]; 
//        Uint32 currentTime = SDL_GetTicks();
//        if (checkBoxAnimationDelay(positions[0], positions[2], currentTime)) {
//
//            waitAnimBoxs[i] = "";
//            
//
//
//            // Set future position
//            boardBoxs[positions[0]][positions[2]].setValue(boardBoxs[positions[0]][positions[2]].getValue());
//            boardNumbers[positions[0]][positions[2]] = 1;
//
//
//
//
//
//            // Set one case FOR display refresh
//            DisplayManagerInstance.removeOneCase(boardBoxs[positions[0]][positions[2]]);
//            DisplayManagerInstance.setOneCase(boardBoxs[positions[0]][positions[2]]);
//
//
//            moveState_i = 1;
//            checkEvents(i + iUser, j + jUser, iUser, jUser);
//
//            
//
//            moveStateMessage_s += "no box collision/";
//
//        }
//    }
//    if (hasNonEmptyStrings(waitAnimBoxs)) {
//        forceMoveAnimation();
//    }
//}



// Check Box anim delay

//bool Game::checkBoxAnimationDelay(int i, int j, Uint32 currentTime)
//{
//    Uint32 lastExecutionTime = boardBoxs[i][j].getLastExecutionTime();
//    Uint32 delayTime = boardBoxs[i][j].delayTime;
//
//    std::cout << currentTime - lastExecutionTime << ">=?" << delayTime << std::endl;
//
//    if (currentTime - lastExecutionTime >= delayTime)
//    {
//        boardBoxs[i][j].setLastExecutionTime(currentTime);
//        return true;
//    }
//
//    return false;
//}
//
//




// Check Bool ------------------------


//void Game::checkEvents(int i, int j, int iUser, int jUser)
//{
//
//   
//
//
//    if (checkBoxExist(i, j))
//    {
//        if (not checkBorderCollide(i, j, iUser, jUser))
//        {
//            if (not checkBoxCollide(i, j, iUser, jUser))
//            {
//                // Time anim synchro
//
//                Uint32 currentTime = SDL_GetTicks();
//
//                if (checkBoxAnimationDelay(i, j, currentTime)) {
//                    // Set future position
//                    boardBoxs[i + iUser][j + jUser].setValue(boardBoxs[i][j].getValue());
//                    boardNumbers[i + iUser][j + jUser] = 1;
//
//
//
//                    // Set old position
//                    boardBoxs[i][j].setValue(0);
//                    setBoardNumbers(i, j, 0);
//
//                    // Set one case FOR display refresh
//                    DisplayManagerInstance.removeOneCase(boardBoxs[i + iUser][j + jUser]);
//                    DisplayManagerInstance.setOneCase(boardBoxs[i + iUser][j + jUser]);
//                    DisplayManagerInstance.removeOneCase(boardBoxs[i][j]);
//
//
//                    moveState_i = 1;
//                    checkEvents(i + iUser, j + jUser, iUser, jUser);
//
//                    // checkBoxAnimationDelay attend mais il ne retente pas d'executer si l'execution n'a pas éé possible en raison du delay, car la boucle parcourt les box mais ne retente pas si les delay ne sont pas fini, il faudrait stocker dans un tableau les Box non move du fait du delay et cela empecherait de moove tant que l'anim n'est pas fini 
//
//                    moveStateMessage_s += "no box collision/";
//                }
//                else {
//                    std::string pushPosition = std::to_string(i + iUser) + '+' + std::to_string(j + jUser);
//                    waitAnimBoxs.push_back(pushPosition);
//                }
//
//
//            }
//            else
//            {
//                moveStateMessage_s += "box collision and no fusion/";
//                //std::cout << "box collide" << std::endl;
//                if (checkIsDouble(i, j, iUser, jUser))
//                {
//                    moveState_i = 1;
//                    //std::cout << "double !!!" << std::endl;
//                    doubleBox(i, j, i + iUser, j + jUser);
//                    setTotalScore(boardBoxs[i + iUser][j + jUser].getValue());
//                    actualizeMaxScore(i + iUser, j + jUser);
//                    moveStateMessage_s += "box collision and fusion/";
//
//                }
//            }
//        }
//        else
//        {
//            moveStateMessage_s += "border collision/";
//        }
//    }
//}