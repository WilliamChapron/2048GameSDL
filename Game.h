#ifndef GAME_H
#define GAME_H

#include "Box.h"
#include <iostream>


struct MoveResult {
    int iUser = 0;
    int jUser = 0;
};

struct MoveState
{
    bool state = false;
    std::string message = "";
};


class Game
{

public:

    Game();
    Game(int boardSize);

    // Get 
    int getSize();
    int getScore();
    int getTotalScore();
    std::vector<std::vector<int>>& getBoardNumbers();
    std::vector<std::vector<Box>>& getBoardBoxs();
    std::string getMessage();

    // Set 
    void setBoardNumbers(int i, int j, int value);

    // Init 
    void initializeGame();
    void initializeBoardBoxs();

    // Game Logic
    void move(int moveEvent);
    void UpLeftCase(int moveEvent);
    void DownRightCase(int moveEvent);

    void doubleBox(int currentBoxI, int currentBoxJ, int nextBoxI, int nextBoxJ);

    void spawnRandomBox();
    void createBox(int i, int j, int value);

    bool checkEnd();

    // Check 

    void checkEvents(int i, int j, int iUser, int jUser);
    bool checkBoxExist(int i, int j);
    bool checkBorderCollide(int i, int j, int iUser, int jUser);
    bool checkBoxCollide(int i, int j, int iUser, int jUser);
    bool checkIsDouble(int i, int j, int iUser, int jUser);


private:
    int moveState_i;
    int size_i;
    int score_i;
    int totalScore_i;
    std::string moveStateMessage_s = "";
    std::vector<std::vector<int>> boardNumbers;
    std::vector<std::vector<Box>> boardBoxs;

    // Check 



    //Tool

    int generateRandomNumber(int min, int max);
    void setTotalScore(int val);
    void actualizeMaxScore(int i, int j);

    // EndCheck

    bool checkBoardFull();
    bool check2048Win();


    void initializeBoard();

    // Move Direction Storage System
    MoveResult eventMoves(int moveEvent);
};

#endif // GAME_H