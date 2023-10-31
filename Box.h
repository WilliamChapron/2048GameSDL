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
    void setValue(int value);
    int generateValue(int playerScore);

    std::vector<int> getPosition();

private:
    int value_i;
    std::vector<int> position_v;
};

