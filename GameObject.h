#pragma once


#include <vector>
#include <string>

class GameObject 
{
public:
    GameObject(); // Base construct
    GameObject(int positionX, int positionY, std::string imagePath); // Create a triangle
    void Update(int i, int j, int value);
    void setImagePath(int value);
    void setPositions(int i, int j);
    

private:
    // Position Board
    int positionI_i; 
    int positionJ_i;


    // Position Display
    int positionX_i;
    int positionY_i;


    std::string imagePath_s;
};
