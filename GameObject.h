#pragma once


#include <vector>
#include <string>
#include <SDL.h>

class GameObject 
{
public:
    //GameObject(); // Base construct
    GameObject(int positionX, int positionY, std::string imagePath); // Create a triangle
    void Update(int i, int j, int value);

    int delayTime;

    Uint32 getLastExecutionTime();

    void setLastExecutionTime(Uint32 time);
    

private:

    // Time Synchro Anim

    
    Uint32 lastExecutionTime;

    // Position Display
    int positionX_i;
    int positionY_i;


    std::string imagePath_s;
};
