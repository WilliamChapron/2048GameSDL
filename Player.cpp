#include "Player.h"
#include <conio.h>
#include <iostream>

Player::Player()
{
}



//int Player::catchKeys()
//{
//    // Using _getch to get the pressed key
//    char keyPressed = _getch();
//
//    switch (keyPressed)
//    {
//    case 72: // Fl�che du haut (ASCII 72)
//        return 1; // i = -1, j = 0
//    case 80: // Fl�che du bas (ASCII 80)
//        return 2;  // i = 1, j = 0
//    case 75: // Fl�che de gauche (ASCII 75)
//        return 3;  // i = 0, j = -1
//    case 77: // Fl�che de droite (ASCII 77)
//        return 4;  // i = 0, j = 1
//    default:
//        return 0;  // Touche non g�r�e
//    }
//}

int Player::catchKeys(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        // Si une touche est enfoncée
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            return 1;
        case SDLK_RIGHT:
            return 2;
        case SDLK_UP:
            return 3;
        case SDLK_DOWN:
            return 4;
        default:
            return 0;
        }
    }
    return 0;
}