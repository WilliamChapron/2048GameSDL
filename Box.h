#pragma once

#include <vector>

#include "GameObject.h"

using namespace std;

class Box : public GameObject
{

public:
    Box();
    Box(int line, int column, int playerScore, int value_i);

    int getValue();
    std::vector<int> getPosition();

    void setValue(int value);
    int generateValue(int playerScore);



private:
    int value_i;
    std::vector<int> position_v;
};

