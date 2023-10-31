#pragma once

#include <SDL.h>
#include <string>

class DisplayManager 
{
public:
    DisplayManager(const char* title, int width, int height, int boardSize);
    ~DisplayManager();

    void clear();
    void present();

    void initializeBoard(int width, int height, int boardSize);
    void setOneCase(int indexI, int indexJ, std::string imagePath);

    SDL_Renderer* getRenderer();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int cellSize;
    int space;
};