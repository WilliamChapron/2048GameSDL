#include "IntegrationTest.h"
#include <iostream>
#include <vector>
#include "Box.h"

IntegrationTest::IntegrationTest() : GameInstance()
{
    functionVector.push_back(&IntegrationTest::fusionTest);
    functionVector.push_back(&IntegrationTest::collideBorderTest);
    functionVector.push_back(&IntegrationTest::collideBoxTest);

    launchFunctions();
}

void IntegrationTest::launchFunctions()
{
    for (void (IntegrationTest::* func)() : functionVector) {
        (this->*func)();
    }


}

void IntegrationTest::fusionTest()
{

    int size = GameInstance.getSize();


    // Init Start Board
    boardConfigStart.resize(size, std::vector<int>(size, 0));
    boardConfigStart[1][1] = 16;
    boardConfigStart[1][2] = 16;

    placeBox(1, 1, 0); // Set board box & numbers
    placeBox(1, 2, 0); // Set board box & numbers

    std::vector<std::vector<Box>>& boardNumbers_r = GameInstance.getBoardBoxs();


    boardNumbers_r[1][1].setValue(16);
    boardNumbers_r[1][2].setValue(16);

    // Init Final Board
    boardConfigFinal.resize(4, std::vector<int>(4, 0));
    boardConfigFinal[1][3] = 32;


    // Fusion Testing
    GameInstance.DownRightCase(4);



    std::cout << "" << std::endl;



    std::cout << "" << std::endl;
    // WHEN TEST WORKING, THERE ARE THE MOVE AND THE FUSION EFFECTIVE IN SAME TIME, so the box change place and double work at the same time


    //  Comparison
    bool result = comparison();
    std::string message = GameInstance.getMessage();

    // Success State Cout
    if (result && message.find("box collision and fusion") != std::string::npos) {
        std::cout << "Le test unitaire a reussi, le message retourne est box collision and fusion" << std::endl;
    }
    else {
        std::cout << "Le test unitaire a echoue" << std::endl;
    }



    for (int i = 0; i < boardNumbers_r.size(); ++i)
    {
        for (int j = 0; j < boardNumbers_r[i].size(); ++j)
        {
            removeBox(i, j, 0);
            boardConfigStart[i][j] = 0;
            boardConfigFinal[i][j] = 0;
        }
    }


}

//------------------------------------------------------------------------------------------------

void IntegrationTest::collideBorderTest()
{

    int size = GameInstance.getSize();
    boardConfigStart.resize(size, std::vector<int>(size, 0));
    boardConfigStart[0][0] = 2;
    boardConfigStart[2][1] = 2;

    placeBox(0, 0, 1); // Set board box & numbers
    placeBox(2, 1, 1); // Set board box & numbers

    // Initialisation of  boardConfigFinal with LEFT move
    boardConfigFinal.resize(4, std::vector<int>(4, 0));
    boardConfigFinal[0][0] = 2;
    boardConfigFinal[2][0] = 2;


    // Collide Border Testing
    GameInstance.UpLeftCase(3);

    std::vector<std::vector<Box>>& boardNumbers_r = GameInstance.getBoardBoxs();





    // Comparison
    bool result = comparison();
    std::string message = GameInstance.getMessage();


    if (result && message.find("border collision") != std::string::npos)
    {
        std::cout << "Le test unitaire a reussi, le message retourne est border collision" << std::endl;
    }
    else
    {
        std::cout << "Le test unitaire a echoue" << std::endl;
    }




    for (int i = 0; i < boardNumbers_r.size(); ++i)
    {
        for (int j = 0; j < boardNumbers_r[i].size(); ++j)
        {
            removeBox(i, j, 0);
            boardConfigStart[i][j] = 0;
            boardConfigFinal[i][j] = 0;
        }
    }
}

void IntegrationTest::collideBoxTest()
{

    int size = GameInstance.getSize();
    boardConfigStart.resize(size, std::vector<int>(size, 0));
    boardConfigStart[1][0] = 16;
    boardConfigStart[1][3] = 2;

    placeBox(1, 0, 1); // Set board box & numbers
    placeBox(1, 3, 1); // Set board box & numbers


    std::vector<std::vector<Box>>& boardNumbers_r = GameInstance.getBoardBoxs();

    boardNumbers_r[1][0].setValue(16);

    // Initialisation of  boardConfigFinal with a RIGHT move
    boardConfigFinal.resize(4, std::vector<int>(4, 0));
    boardConfigFinal[1][3] = 2;
    boardConfigFinal[1][2] = 16;


    // Collide Box Testing
    GameInstance.DownRightCase(4);

    /*for (int i = 0; i < boardNumbers_r.size(); ++i) {
        for (int j = 0; j < boardNumbers_r[i].size(); ++j) {
            std::cout << boardNumbers_r[i][j].getValue() << std::endl;
        }
    }

    std::cout << "" << std::endl;

    for (int i = 0; i < boardNumbers_r.size(); ++i) {
        for (int j = 0; j < boardNumbers_r[i].size(); ++j) {
            std::cout << boardConfigFinal[i][j] << std::endl;
        }
    }
    std::cout << "" << std::endl;*/




    //comparaison
    bool result = comparison();
    std::string message = GameInstance.getMessage();


    if (result && message.find("box collision and no fusion") != std::string::npos)
    {
        std::cout << "Le test unitaire a reussi, il y a une box collision sans fusion" << std::endl;
    }
    else
    {
        std::cout << "Le test unitaire a echoue" << std::endl;
    }

    for (int i = 0; i < boardNumbers_r.size(); ++i) {
        for (int j = 0; j < boardNumbers_r[i].size(); ++j) {
            removeBox(i, j, 0);
            boardConfigStart[i][j] = 0;
            boardConfigFinal[i][j] = 0;
        }
    }

}

bool IntegrationTest::comparison()
{
    int size = GameInstance.getSize();
    bool comparison = true;

    std::vector<std::vector<Box>>& boardNumbers_r = GameInstance.getBoardBoxs();// Object board to compare with finalConfigBoard

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (boardNumbers_r[i][j].getValue() != boardConfigFinal[i][j])
            {
                comparison = false;
            }
        }
    }
    return comparison;
}




void IntegrationTest::placeBox(int i, int j, int value) {
    GameInstance.createBox(i, j, value);
    GameInstance.setBoardNumbers(i, j, 1);
}

void IntegrationTest::removeBox(int i, int j, int value) {
    std::vector<std::vector<Box>>& boardBoxs_r = GameInstance.getBoardBoxs();
    boardBoxs_r[i][j].setValue(value);
    GameInstance.setBoardNumbers(i, j, 0);
}
