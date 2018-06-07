//
// Created by George Kobelev on 6/27/17.
//

#ifndef PROGBASE3_DATA_LOADER_H
#define PROGBASE3_DATA_LOADER_H

#include <collections/game.h>

/**
 * @brief upload map data to game
 * @param[out] game to set map parameters
 */
void uploadData(Game * game);

/**
 * @brief free memory from map data
 * @param[out] game  to free memory
 */
void unloadData(Game * game);

#endif //PROGBASE3_DATA_LOADER_H
