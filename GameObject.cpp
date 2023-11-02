#include "GameObject.h"
#include <iostream>


GameObject::GameObject(int positionX, int positionY, std::string imagePath) : positionX_i(positionX), positionY_i(positionY), imagePath_s(imagePath), lastExecutionTime(0), delayTime(1000) // Create a triangle 
{
}

void GameObject::Update(int i, int j, int value)
{
}

Uint32 GameObject::getLastExecutionTime()
{
    return lastExecutionTime;
    //std::cout << "get LastExtime" << getLastExecutionTime() << std::endl;
}

void GameObject::setLastExecutionTime(Uint32 time)
{
    lastExecutionTime = time;
    //std::cout << "new LastExtime" << lastExecutionTime << std::endl;

}
