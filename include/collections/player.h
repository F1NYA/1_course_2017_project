//
// Created by George Kobelev on 6/27/17.
//

#ifndef PROGBASE3_PLAYER_H
#define PROGBASE3_PLAYER_H

#include "vector.h"

//enum STATE{GROUND, FALLING, MOVING, DUCKING};

/**
 * @struct Player
 * @brief Structure for .
 * @var Game::surface
 * Member 'surface' is a poiter to structure that contains a collection of pixels used in software blitting.
 * @var Game::player
 * Member 'player' is a structure that contains player statement.
 * @var Game::sectors
 * Member 'sectors' is a realisation of dynamic array.
 * @var Game::numSectors
 * Member 'numSectors' is number of sectors in game.
 */
typedef struct player {
    XYZ where, velocity;
    double angle, anglesin, anglecos, yaw;
    unsigned int sector;
}Player;

#endif //PROGBASE3_PLAYER_H
