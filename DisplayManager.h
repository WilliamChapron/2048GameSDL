#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "Box.h"

class DisplayManager 
{
public:
    DisplayManager();
    DisplayManager(const char* title, int width, int height, int boardSize, int score, int totalScore);
    ~DisplayManager();


    std::string getImagePath(int value);
    std::vector<int> getPositions(int i, int j);

    void clear();
    void present();

    int getWidth();
    int getHeight();
    int getBoardSize();

    void initializeBoard();

    void setOneCase(Box boxObject);
    void removeOneCase(Box boxObject);

    SDL_Renderer* getRenderer();

    void displayText(int textSize, int width, int height, int boardSize, int score, int totalScore);
    void eraseText(int textSize, int width, int height, int boardSize);
    void displayLoseText(int textSize, int width, int height, int boardSize, int score, int totalScore);
    void displayWinText(int textSize, int width, int height, int boardSize, int score, int totalScore);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<std::vector<SDL_Rect>> rectangles;

    int cellSize_i;
    int space_i;
    int width_i;
    int height_i;
    int boardSize_i;
};