#ifndef PLAYER_H
#define PLAYER_H

#include <sdl.h>

class Player {
public:
    Player();
    int catchKeys(SDL_Event& e);

};

#endif // PLAYER_H