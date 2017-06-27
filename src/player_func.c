//
// Created by George Kobelev on 6/27/17.
//

#include <player_func.h>
#include <macros.h>

void MovePlayer(Game * game, double dx, double dy) {
    double px = game->player.where.x, py = game->player.where.y;

    Sector* const sect = &(game->sectors)[game->player.sector];
    XY* const vert = sect->vertex;
    for(unsigned s = 0; s < (sect->npoints); ++s)
    {
        if (sect->neighbors[s] >= 0
            && IntersectBox(px, py, px + dx, py + dy, vert[s + 0].x, vert[s + 0].y, vert[s + 1].x, vert[s + 1].y)
            && PointSide(px + dx, py + dy, vert[s + 0].x, vert[s + 0].y, vert[s + 1].x, vert[s + 1].y) < 0)
        {
            game->player.sector = (unsigned)sect->neighbors[s];
            break;
        }
    }

    game->player.where.x += dx;
    game->player.where.y += dy;
    game->player.anglesin = sin(game->player.angle);
    game->player.anglecos = cos(game->player.angle);
}