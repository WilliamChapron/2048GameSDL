#include "DisplayManager.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


DisplayManager::DisplayManager() 
{

}

DisplayManager::DisplayManager(const char* title, int width, int height, int boardSize) : window(nullptr), renderer(nullptr), cellSize_i(0), space_i(0), width_i(width), height_i(height), boardSize_i(boardSize)
{
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Impossible d'initialiser SDL : " << SDL_GetError() << std::endl;
        return;
    }

    // Créer une fenêtre
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Impossible de créer la fenêtre : " << SDL_GetError() << std::endl;
        return;
    }

    // Créer un rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Impossible de créer le rendu : " << SDL_GetError() << std::endl;
        return;
    }

    clear();

    int minSize = std::min(width_i, height_i);
    int maxSize = std::max(width_i, height_i);
    space_i = minSize / 100;// space est l'ecart entre les cases
    cellSize_i = (minSize - ((boardSize_i + 1) * space_i)) / boardSize;

    initializeBoard();
}


DisplayManager::~DisplayManager()
{
    // Libérer les ressources
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}


SDL_Renderer* DisplayManager::getRenderer()
{
    return renderer;
}

void DisplayManager::clear() 
{
    // Effacer le rendu en noir
    SDL_SetRenderDrawColor(renderer, 200, 200, 175, 255);
    SDL_RenderClear(renderer);
}

void DisplayManager::present() 
{
    // Mettre à jour le rendu
    SDL_RenderPresent(renderer);
}






void DisplayManager::initializeBoard()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255); // couleur beige pour les

    // Initialisation du tableau de rectangles
    rectangles.resize(boardSize_i, std::vector<SDL_Rect>(boardSize_i));

    for (int i = 0; i < boardSize_i; ++i)
    {
        for (int j = 0; j < boardSize_i; ++j)
        {
            int x = space_i + (j * (cellSize_i + space_i));
            int y = space_i + (i * (cellSize_i + space_i));

            rectangles[i][j] = { x, y, cellSize_i, cellSize_i };
            SDL_RenderFillRect(renderer, &rectangles[i][j]);
        }
    }

    // Mettre à jour le rendu
    present();
}

//void DisplayManager::displayText(int width, int height)
//{
//	// std::string text = "My score :";
//    // int x = space_i + boardSize * (space_i + cellSize_i) + width/50;
//    // int y = height / 2;
//
//	// for (char c : text) 
//    // {
//	// 	// Charger la texture du caractère c
//	// 	SDL_Texture* charTexture = loadCharTexture(c); 
//
//	// 	// Afficher la texture du caractère
//	// 	SDL_Rect charRect = { x, y, 10, 10 };
//	// 	SDL_RenderCopy(renderer, charTexture, nullptr, &charRect);
//
//	// 	// Déplacez x pour le caractère suivant
//	// 	x += 12; 
//	// }
//
//	TTF_Font* font = TTF_OpenFont("path_to_your_font_file.ttf", 12); 
//	if (!font)
//	{
//		std::cerr << "Impossible de charger la police : " << TTF_GetError() << std::endl;
//		return;
//	}
//
//	int x = space_i + boardSize * (space_i + cellSize_i) + width / 50;
//	int y = height / 2;
//	std::string text = "My Score : TEST"
//
//	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
//	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//
//	SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
//	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
//
//	SDL_FreeSurface(textSurface);
//	SDL_DestroyTexture(textTexture);
//	TTF_CloseFont(font);
//}

void DisplayManager::setOneCase(Box boxObject)
{

    std::vector<int> positions = boxObject.getPosition();
    int value = boxObject.getValue();

    std::string imagePath = getImagePath(value);

    std::cout << "Setting case at (" << positions[0] << ", " << positions[1] << ") with value " << value << std::endl;
    

    // Charger une image avec SDL_image
    std::cout << imagePath << std::endl;
    if (imagePath != "") {
        const char* imagePath_c = imagePath.c_str();
        SDL_Surface* imageSurface = SDL_LoadBMP(imagePath_c);
        SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

        // Libérer la surface puisque la texture a été créée
        SDL_FreeSurface(imageSurface);

        // Copier la texture sur le rendu avec rect (object)
        SDL_Rect& rect = rectangles[positions[0]][positions[1]];
        SDL_RenderCopy(renderer, imageTexture, NULL, &rect);

        // Mettre à jour le rendu
        std::cout << "Mettre a jour le rendu:" << std::endl;
        present();
    }
}



void DisplayManager::removeOneCase(Box boxObject)
{
    std::vector<int> positions = boxObject.getPosition();

    std::cout << "Setting case at (" << positions[0] << ", " << positions[1] << ") with value " << 0 << std::endl;
    SDL_Rect& rect = rectangles[positions[0]][positions[1]];

    SDL_RenderFillRect(renderer, &rect);

    std::cout << "Mettre a jour le rendu:" << std::endl;

    present();
}

std::vector<int> DisplayManager::getPositions(int i, int j)
{
    int posX = space_i + (i * (cellSize_i + space_i));
    int posY = space_i + (j * (cellSize_i + space_i));

    return { posX, posY };
}

std::string DisplayManager::getImagePath(int value)
{
    switch (value) 
    {
    case 0:
        return "";
    case 2:
        return "./img/2.bmp";
    case 4:
        return "./img/4.bmp";
    case 8:
        return "./img/8.bmp";
    case 16:
        return "./img/16.bmp";
    case 32:
        return "./img/32.bmp";
    case 64:
        return "./img/64.bmp";
    case 128:
        return "./img/128.bmp";
    case 256:
        return "./img/256.bmp";
    case 512:
        return "./img/512.bmp";
    case 1024:
        return "./img/1024.bmp";
    case 2048:
        return "./img/2048.bmp";
    default:
        return "";
    }
}
