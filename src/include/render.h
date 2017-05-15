//
// Created by George Kobelev on 5/11/17.
//

#ifndef PROGBASE3_RENDER_H
#define PROGBASE3_RENDER_H

#include <SDL.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

static struct sector {
    double floor, ceil;
    struct xy {double x, y;} *vertex;

} *sectors = NULL;

static struct player {
    struct xyz {double x, y, z;} where, velocity;
    unsigned int sector;
} player;

static SDL_Surface *surface = NULL;


#endif //PROGBASE3_RENDER_H
