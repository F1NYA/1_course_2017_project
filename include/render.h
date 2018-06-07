//
// Created by George Kobelev on 5/11/17.
//

#ifndef PROGBASE3_RENDER_H
#define PROGBASE3_RENDER_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <collections/player.h>
#include <collections/sector.h>
#include <collections/game.h>

/**
 * @brief drawing
 * @param game using for game statement;
 */
void DrawScreen(Game * game);

#endif //PROGBASE3_RENDER_H