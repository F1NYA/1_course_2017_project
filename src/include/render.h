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

#define W 608
#define H 480

#define EyeHeight  6
#define DuckHeight 2.5
#define HeadMargin 1
#define KneeHeight 2
#define hfov (0.73f*H)
#define vfov (.2f*H)



#define clamp(a, mi,ma)      min(max(a,mi),ma)
#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })


struct xy { float x, y;};

static struct sector {
    float floor, ceil;
    struct xy *vertex;
    signed char *neighbors;
    unsigned int npoints;
} *sectors = NULL;

static unsigned NumSectors = 0;

static struct player {
    struct xyz {float x, y, z;} where, velocity;
    float angle, anglesin, anglecos, yaw;
    unsigned int sector;
} player;

SDL_Surface *surface;

void LoadData();
void UnloadData();
/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
void vline(int x, int y1,int y2, int top,int middle,int bottom);
void MovePlayer(float dx, float dy);
void DrawScreen();

#endif //PROGBASE3_RENDER_H
