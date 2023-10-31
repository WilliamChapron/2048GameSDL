#pragma once

union SDL_Event;

class Player {
public:
    Player();
    int catchKeys(SDL_Event& e);
    int catchKeys();

};
