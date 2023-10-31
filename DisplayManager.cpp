#include "DisplayManager.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <SDL.h>
#include <SDL_image.h>




DisplayManager::DisplayManager(const char* title, int width, int height, int boardSize) : window(nullptr), renderer(nullptr), cellSize(0), space(0)
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

    int minSize = std::min(width, height);
    int maxSize = std::max(width, height);
    space = minSize / 100;// space est l'ecart entre les cases
    cellSize = (minSize - ((boardSize + 1) * space)) / boardSize;

    initializeBoard(width, height, boardSize);
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

void DisplayManager::clear() {
    // Effacer le rendu en noir
    SDL_SetRenderDrawColor(renderer, 200, 200, 175, 255);
    SDL_RenderClear(renderer);
}

void DisplayManager::present() {
    // Mettre à jour le rendu
    SDL_RenderPresent(renderer);
}


void DisplayManager::initializeBoard(int width, int height, int boardSize)
{
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //couleur blanche en fond
    //SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255);// couleur beige pour les cases

    for (int row = 0; row < boardSize; ++row)
    {
        for (int col = 0; col < boardSize; ++col)
        {
            int x = space + (col * (cellSize + space));
            int y = space + (row * (cellSize + space));
            SDL_Rect rect = { x, y, cellSize, cellSize };
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    // Mettre à jour le rendu
    present();
}


void DisplayManager::setOneCase(int indexI, int indexJ, std::string imagePath)
{

    int posI = space + (indexI * (cellSize + space));
    int posJ = space + (indexJ * (cellSize + space));

    const char* imagePath_c = imagePath.c_str();

    // Charger une image avec SDL_image
    SDL_Surface* imageSurface = SDL_LoadBMP(imagePath_c);
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

    // Libérer la surface puisque la texture a été créée
    SDL_FreeSurface(imageSurface);

    // Copier la texture sur le rendu
    SDL_Rect destinationRect = { 100, 100, 200, 200 }; // Rectangle de destination (x, y, largeur, hauteur)
    SDL_RenderCopy(renderer, imageTexture, NULL, &destinationRect);

    // Mettre à jour le rendu
    present();
}
