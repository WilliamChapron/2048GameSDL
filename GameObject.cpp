#include "GameObject.h"
#include <iostream>;

GameObject::GameObject() : positionI_i(0), positionJ_i(0), positionX_i(0), positionY_i(0), imagePath_s("")
{
    

}

GameObject::GameObject(int positionX, int positionY, std::string imagePath) : positionX_i(positionX), positionY_i(positionY), imagePath_s(imagePath) // Create a triangle 
{
}

void GameObject::Update(int i, int j, int value)
{

    setImagePath(value);
    setPositions(i, j);

    //std::cout << imagePath_s << std::endl;
    //std::cout << positionI_i << "Update" << std::endl;
    //std::cout << positionJ_i << "Update" << std::endl;
}




void GameObject::setImagePath(int value)
{
    switch (value) {
    case 0:
        imagePath_s = "path_vers_image_2";
        break;
    case 2:
        imagePath_s = "path_vers_image_2";
        break;
    case 4:
        imagePath_s = "path_vers_image_4";
        break;
    case 8:
        imagePath_s = "path_vers_image_8";
        break;
    case 16:
        imagePath_s = "path_vers_image_16";
        break;
    case 32:
        imagePath_s = "path_vers_image_32";
        break;
    case 64:
        imagePath_s = "path_vers_image_64";
        break;
    case 128:
        imagePath_s = "path_vers_image_128";
        break;
    case 256:
        imagePath_s = "path_vers_image_256";
        break;
    case 512:
        imagePath_s = "path_vers_image_512";
        break;
    case 1024:
        imagePath_s = "path_vers_image_1024";
        break;
    case 2048:
        imagePath_s = "path_vers_image_2048";
        break;
    default:
        break;
    }
}


void GameObject::setPositions(int i, int j)
{
    positionI_i = i;
    positionJ_i = j;

}
