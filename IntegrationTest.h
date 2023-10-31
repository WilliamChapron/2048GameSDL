#ifndef INTEGRATIONTEST_H
#define INTEGRATIONTEST_H

#include <vector>
#include <iostream>
#include "Game.h"
#include "Box.h"

class IntegrationTest {
public:
    IntegrationTest();
    void launchFunctions();
    void placeBox(int i, int j, int value);
    void removeBox(int i, int j, int value);


    void fusionTest();
    void collideBoxTest();
    void collideBorderTest();

    bool comparison();




private:
    std::vector<void (IntegrationTest::*)()> functionVector;

    std::vector<std::vector<int>> boardConfigStart;
    std::vector<std::vector<int>> boardConfigFinal;



    Game GameInstance;
};

#endif // INTEGRATIONTEST_H