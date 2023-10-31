#ifndef BOX_H
#define BOX_H

#include <vector>

using namespace std;

class Box
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

#endif // BOX_H