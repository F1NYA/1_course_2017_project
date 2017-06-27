//
// Created by George Kobelev on 6/27/17.
//

#ifndef PROGBASE3_PLAYER_FUNC_H
#define PROGBASE3_PLAYER_FUNC_H

#include <collections/game.h>

/**
 * @brief check for collision and set new pos for player
 * @param game to access for curr player state
 * @param dx {x} of velocity vector
 * @param dy {y} of velocity vector
 */
void MovePlayer(Game * game, XY dvec);

#endif //PROGBASE3_PLAYER_FUNC_H
