//
// Created by George Kobelev on 6/4/17.
//

#ifndef PROGBASE3_MACROSES_H
#define PROGBASE3_MACROSES_H

#include <collections/game.h>

#undef max
#undef min
#undef clamp

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

#define clamp(a, mi,ma)      min(max(a,mi),ma)

#define W 2048
#define H 1080

#define EyeH  6
#define DuckH 2.5
#define HeadM 1
#define KneeH 2
#define hfov (0.73f*H)
#define vfov (.2f*H)

#define NEAR_Z 1e-4f
#define FAR_Z  5
#define NEAR_X 1e-5f
#define FAR_X 20.f

#define vecCrossProd(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap_range:  Calc if two number ranges overlap.
#define Overlap_range(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox2D: Determine whether two 2D-boxes intersect.
#define IntersectBox2D(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap_range(x0,x1,x2,x3) && Overlap_range(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vecCrossProd((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// IntersectLines: Calculate the point of intersection between two lines.
#define IntersectLines(x0,y0, x1,y1, x2,y2, x3,y3) ((struct xy) { \
    vecCrossProd(vecCrossProd(x0,y0, x1,y1), (x0)-(x1), vecCrossProd(x2,y2, x3,y3), (x2)-(x3)) / vecCrossProd((x0)-(x1), (y0)-(y1), (x2)-(x3), (y2)-(y3)), \
    vecCrossProd(vecCrossProd(x0,y0, x1,y1), (y0)-(y1), vecCrossProd(x2,y2, x3,y3), (y2)-(y3)) / vecCrossProd((x0)-(x1), (y0)-(y1), (x2)-(x3), (y2)-(y3)) })

#define Yaw(y,z) (y + z * (game->player.yaw))

#endif //PROGBASE3_MACROSES_H
