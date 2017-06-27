//
// Created by George Kobelev on 6/27/17.
//

#ifndef PROGBASE3_GAME_H
#define PROGBASE3_GAME_H

#include <SDL2/SDL.h>
#include "player.h"
#include "sector.h"

typedef struct game{
    SDL_Surface * surface;
    Player player;
    Sector * sectors;
    int numSectors;
}Game;

#endif //PROGBASE3_GAME_H