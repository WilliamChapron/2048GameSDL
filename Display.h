#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <vector>
#include "Box.h"

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