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



typedef struct xy { float x, y;} XY;

typedef struct sector {
    double floor, ceil;
    XY *vertex;
    signed char *neighbors;
    unsigned int npoints;
}Sector;

static Sector *sectors = NULL;

static unsigned NumSectors = 0;

typedef struct player {
    struct xyz {double x, y, z;} where, velocity;
    double angle, anglesin, anglecos, yaw;
    unsigned int sector;
}Player;

static Player player;

typedef struct item { int sectorno, sx1, sx2; } Item;

SDL_Surface *surface;

void LoadData();
void UnloadData();
/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
void vline(int x, int y1, int y2, int top, int middle, int bottom);
void MovePlayer(double dx, double dy);
void DrawScreen();

#endif //PROGBASE3_RENDER_H
