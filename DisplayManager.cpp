#include "DisplayManager.h"
#include <iostream>




DisplayManager::DisplayManager(const char* title, int width, int height) : window(nullptr), renderer(nullptr) 
{
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cerr << "Impossible d'initialiser SDL : " << SDL_GetError() << std::endl;
        return;
    }

    // Cr�er une fen�tre
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) 
    {
        std::cerr << "Impossible de cr�er la fen�tre : " << SDL_GetError() << std::endl;
        return;
    }

    // Cr�er un rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Impossible de cr�er le rendu : " << SDL_GetError() << std::endl;
        return;
    }
}


DisplayManager::~DisplayManager()
{
    // Lib�rer les ressources
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void DisplayManager::present() {
    // Mettre � jour le rendu
    SDL_RenderPresent(renderer);
}

