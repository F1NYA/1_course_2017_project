//
// Created by George Kobelev on 6/27/17.
//

#ifndef PROGBASE3_PLAYER_H
#define PROGBASE3_PLAYER_H

#include "vector.h"

//enum STATE{GROUND, FALLING, MOVING, DUCKING};

typedef struct player {
    XYZ where, velocity;
    double angle, anglesin, anglecos, yaw;
    unsigned int sector;
}Player;

#endif //PROGBASE3_PLAYER_H
