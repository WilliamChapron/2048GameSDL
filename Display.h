#ifndef DISPLAY_H
#define DISPLAY_H

#include "Box.h"

class vector;

class Display
{
public:
    void displayNumber(int number);

    void displayBoard(std::vector<std::vector<int>>& boardNumbers, std::vector<std::vector<Box>>& boardBoxs, int size);

    void clearScreen();

private:

    void displayHorizontalLine();
    void displayBorder();

};

#endif // DISPLAY_H