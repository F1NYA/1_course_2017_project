//
// Created by George Kobelev on 6/27/17.
//

#ifndef PROGBASE3_GAME_H
#define PROGBASE3_GAME_H

#include <SDL2/SDL.h>
#include "player.h"
#include "sector.h"

/**
 * @struct Game
 * @brief Structure to save and give access for main variables.
 * @var Game::surface
 * Member 'surface' is a poiter to structure that contains a collection of pixels used in software blitting.
 * @var Game::player
 * Member 'player' is a structure that contains player statement.
 * @var Game::sectors
 * Member 'sectors' is a realisation of dynamic array.
 * @var Game::numSectors
 * Member 'numSectors' is number of sectors in game.
 */
typedef struct game{
    SDL_Surface * surface;
    Player player;
    Sector * sectors;
    int numSectors;
}Game;

#endif //PROGBASE3_GAME_H
