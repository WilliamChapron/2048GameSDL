#include "Display.h"

#include <iostream>
#include <iomanip>
#include "Box.h"

void Display::displayNumber(int number) {
    if (number == 0) {
        std::cout << std::setw(4) << "";
    }
    else {
        std::cout << std::setw(4) << number;
    }

}

void Display::displayBoard(std::vector<std::vector<int>>& boardNumbers, std::vector<std::vector<Box>>& boardBoxs, int size) {
    clearScreen();

    // Afficher la grille du jeu
    for (int i = 0; i < boardNumbers.size(); ++i) {
        displayHorizontalLine();

        displayBorder();

        for (int j = 0; j < size; ++j) {
            displayBorder();
            if (boardBoxs[i][j].getValue() != 0)
            {
                displayNumber(boardBoxs[i][j].getValue());
            }
            else {
                displayNumber(0);
            }


            displayBorder();
        }

        displayBorder();
        std::cout << std::endl;
    }

    displayHorizontalLine();
}

void Display::clearScreen() {
    system("cls");

}

void Display::displayHorizontalLine() {
    std::cout << "----------------------------------------------------" << std::endl;
}

void Display::displayBorder() {
    std::cout << "|";
}