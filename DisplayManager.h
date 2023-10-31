#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <SDL.h>

class DisplayManager {
public:
    DisplayManager( const char* title, int width, int height);
    ~DisplayManager();

    void clear();
    void present();

    SDL_Renderer* getRenderer();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // DISPLAYMANAGER_H
