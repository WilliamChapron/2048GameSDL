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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void DisplayManager::present() {
    // Mettre à jour le rendu
    SDL_RenderPresent(renderer);
}

