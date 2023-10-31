#include "main.h"
#include "Game.h"
#include "Player.h"
#include "Display.h"
#include "Box.h"
#include "Player.h"
#include "IntegrationTest.h"
#include "DisplayManager.h"

#include <SDL.h>



#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>




using namespace std;

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(0)));



    // Instance Part with the size of the grid
    Game GameInstance(4);

    std::vector<std::vector<int>>& boardNumbers_r = GameInstance.getBoardNumbers(); //grid that shows the existence of boxes (1 or 0)
    std::vector<std::vector<Box>>& boardBoxs_r = GameInstance.getBoardBoxs();

    Display DisplayInstance;
    DisplayInstance.displayBoard(boardNumbers_r, boardBoxs_r, GameInstance.getSize());

    Player PlayerInstance;


    /*IntegrationTest IntegrationTestInstance;*/

     /*In Game */
     while (true) 
     {   
         int moveEvent = PlayerInstance.catchKeys(); // Catch keys for move
         if (moveEvent != 0) 
         {
             GameInstance.move(moveEvent);
             DisplayInstance.displayBoard(boardNumbers_r, boardBoxs_r, GameInstance.getSize()); // Refresh display
             /*cout << "Total Score : "<< GameInstance.getTotalScore() << endl;
             cout << "Max Number : " << GameInstance.getScore() << endl;*/
             if (GameInstance.checkEnd())
             {
             	cout << "Fin de partie." << endl;
                 /*break;*/
             }
         } 
     }

     // Unitair Test
    /*while (true) {

    }*/

    // SDL test

    /*while (true) {


    }*/

    return 0;
}


//int main(int argc, char* argv[]) {
//    DisplayManager display("2048", 800, 600);
//
//
//    bool quit = false;
//    SDL_Event e;
//    Player PlayerInstance;
//    Game GameInstance(4);
//
//    //std::vector<std::vector<int>>& boardNumbers_r = GameInstance.getBoardNumbers(); //grid that shows the existence of boxes (1 or 0)
//    //std::vector<std::vector<Box>>& boardBoxs_r = GameInstance.getBoardBoxs();
//    // Display here fist board
//
//    while (!quit) {
//        if (SDL_PollEvent(&e) != 0) {
//            int moveEvent = PlayerInstance.catchKeys(e);
//            cout << moveEvent << std::endl;
//            cout << "" << std::endl;
//            if (moveEvent != 0)
//            {
//                GameInstance.move(moveEvent);
//                //Refresh Display
//                if (GameInstance.checkEnd())
//                {
//                    cout << "Fin de partie." << endl;
//                    /*break;*/
//                }
//            }
//            if (e.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//    }
//
//    return 0;
//}

