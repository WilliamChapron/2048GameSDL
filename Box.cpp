
#include "Box.h"
#include <iostream>

// Constructor------------------------

Box::Box()
{
    value_i = 0;
    position_v = { 0,0 };
}

Box::Box(int line, int column, int playerScore, int value)
{
    position_v = { line, column };

    if (value == 1)
    {
        value_i = 2;
    }
    else
    {
        value_i = (value != 0) ? generateValue(playerScore) : value;
    }
}


// Get -----------------------------

int Box::getValue()
{
    return value_i;
}

std::vector<int> Box::getPosition()
{
    return position_v;
}

//Tools -----------------------------

void Box::setValue(int value)
{
    value_i = value;
    //std::cout << value_i << std::endl;
}


int Box::generateValue(int playerScore)
{
    int generatedValue;

    int randVal = rand() % 10; // Generate random value between 0 and 9

    // In the 2048 game, 90% chance to get a 4-valued box
    if (randVal < 9)
    {
        generatedValue = 2;
    }
    else
    {
        generatedValue = 4;
    }

    return generatedValue;
}

