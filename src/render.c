//
// Created by George Kobelev on 5/11/17.
//

#include <render.h>
#include <macros.h>

typedef struct item { int secNo, sx1, sx2; } Item;
enum { MaxQueue = 16 };  // maximum number of portal renders

void setPixel(SDL_Surface * surface, int posx, int posy, int value){
    ((int*)surface->pixels)[posy*W+posx] = value;
}

void setnarr(int *arr, int value, int num) {
    for (int i = 0; i < num; ++i) arr[i] = value;
}

void line(SDL_Surface * surface, int x, int y1, int y2, int top, int mid, int bot) {
    if (y2==y1) setPixel(surface, x, y1, mid);
    else if (y2>y1) {
        setPixel(surface, x, y1, top);
        for (int y = y1+1; y < y2; ++y) setPixel(surface, x, y, mid);
        setPixel(surface, x, y2, bot);
    }
}

void DrawScreen(Game * game) {
    //incode queue realisation
    Item queue[MaxQueue],
            *head = queue,
            *tail = queue;

    int ytop[W] = {0}, ybottom[W], rendSects[game->numSectors];

    setnarr(ybottom, H-1, W);
    setnarr(rendSects, 0, game->numSectors);

    /* Begin whole-screen rendering from where the player is. */
    *head = (Item) { game->player.sector, 0, W-1 };
    ++head;

    do {
        /* Deque current sector to draw */
        Item curr = *tail;
        if(++tail == (queue+MaxQueue)) tail = queue;

        if(rendSects[curr.secNo] == 33) continue; // 32 = stop render
        ++rendSects[curr.secNo];
        Sector* sect = &(game->sectors)[curr.secNo];

        /* Render each wall of this sector that is facing towards player. */
        for(int s = 0; s < sect->npoints; ++s) {

            /* Calc the x,y coordinates of the two endpoints of this edge */
            double vx1 = (sect->vertex[s].x  -  game->player.where.x);
            double vy1 = (sect->vertex[s].y  -  game->player.where.y);
            double vx2 = (sect->vertex[s+1].x - game->player.where.x);
            double vy2 = (sect->vertex[s+1].y - game->player.where.y);

            /* Rotate them around the player's view */
            double rx1 = vx1 * game->player.anglesin - vy1 * game->player.anglecos;
            double rx2 = vx2 * game->player.anglesin - vy2 * game->player.anglecos;
            double rz1 = vx1 * game->player.anglecos + vy1 * game->player.anglesin;
            double rz2 = vx2 * game->player.anglecos + vy2 * game->player.anglesin;

            /* Is the wall partially in front of the player? */
            if(rz1 <= 0 && rz2 <= 0) continue;

            /* If it's partially behind the player, clip it against player's view frustrum */
            if(rz1 <= 0 || rz2 <= 0) {
                // Find an intersection between the wall and the approximate edges of player's view
                XY i1 = Intersect(rx1,rz1,rx2,rz2, -NEAR_SIDE, NEAR_Z, -FAR_SIDE, FAR_Z);
                XY i2 = Intersect(rx1,rz1,rx2,rz2,  NEAR_SIDE, NEAR_Z,  FAR_SIDE, FAR_Z);

                if(rz1 < NEAR_Z) {
                    if(i1.y > 0) {
                        rx1 = i1.x;
                        rz1 = i1.y;
                    } else {
                        rx1 = i2.x;
                        rz1 = i2.y;
                    }
                }
                if(rz2 < NEAR_Z) {
                    if(i1.y > 0) {
                        rx2 = i1.x;
                        rz2 = i1.y;
                    } else {
                        rx2 = i2.x;
                        rz2 = i2.y;
                    }
                }
            }

            /* Perspective transform */
            double xscale1 = hfov / rz1;
            double yscale1 = vfov / rz1;
            double xscale2 = hfov / rz2;
            double yscale2 = vfov / rz2;

            int x1 = W/2 - (int)(rx1 * xscale1);
            int x2 = W/2 - (int)(rx2 * xscale2);

            if(x1 >= x2 || x2 < curr.sx1 || x1 > curr.sx2) continue; // Render if it's visible

            /* Acquire the floor and ceiling heights, relative to where the player's view is */
            double yceil  = sect->ceil  - game->player.where.z;
            double yfloor = sect->floor - game->player.where.z;

            /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
            int neighbor = sect->neighbors[s];
            double nyceil = 0, nyfloor = 0;

            if(neighbor >= 0) // Is another sector showing through this portal?
            {
                nyceil  = game->sectors[neighbor].ceil  - game->player.where.z;
                nyfloor = game->sectors[neighbor].floor - game->player.where.z;
            }

            /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
            int y1a  = H/2 - (int)(Yaw(yceil, rz1) * yscale1),  y1b = H/2 - (int)(Yaw(yfloor, rz1) * yscale1);
            int y2a  = H/2 - (int)(Yaw(yceil, rz2) * yscale2),  y2b = H/2 - (int)(Yaw(yfloor, rz2) * yscale2);

            /* The same for the neighboring sector */
            int ny1a = H/2 - (int)(Yaw(nyceil, rz1) * yscale1), ny1b = H/2 - (int)(Yaw(nyfloor, rz1) * yscale1);
            int ny2a = H/2 - (int)(Yaw(nyceil, rz2) * yscale2), ny2b = H/2 - (int)(Yaw(nyfloor, rz2) * yscale2);

            /* Render the wall. */
            int beginx = max(x1, curr.sx1), endx = min(x2, curr.sx2);
            for(int i = beginx; i <= endx; ++i)
            {
                /* Calculate the Z coordinate for this point. (Only used for lighting.) */
                int z = (int)((i - x1) * (rz2-rz1) / (x2-x1) + rz1) * 8;

                /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
                int ya = (i - x1) * (y2a-y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[i],ybottom[i]); // top
                int yb = (i - x1) * (y2b-y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[i],ybottom[i]); // bottom

                /* Render ceiling: everything above this sector's ceiling height. */
                line(game->surface, i, ytop[i], cya - 1, 0x111111, 0x222222, 0x111111);
                /* Render floor: everything below this sector's floor height. */
                line(game->surface, i, cyb + 1, ybottom[i], 0x0000FF, 0x0000AA, 0x0000FF);

                /* Is there another sector behind this edge? */
                if(neighbor >= 0)
                {
                    /* Same for _their_ floor and ceiling */
                    int nya = (i - x1) * (ny2a-ny1a) / (x2-x1) + ny1a, cnya = clamp(nya, ytop[i],ybottom[i]);
                    int nyb = (i - x1) * (ny2b-ny1b) / (x2-x1) + ny1b, cnyb = clamp(nyb, ytop[i],ybottom[i]);

                    /* If our ceiling is higher than their ceiling, render upper wall */
                    unsigned r1 = (unsigned)0x010101 * (255-z), r2 = (unsigned)0x040007 * (31-z/8);
                    line(game->surface, i, cya, cnya - 1, 0, ((i == x1 || i == x2) ? (0) : (r1)), 0); // Between our and their ceiling
                    ytop[i] = clamp(max(cya, cnya), ytop[i], H-1);   // Shrink the remaining window below these ceilings

                    /* If our floor is lower than their floor, render bottom wall */
                    line(game->surface, i, cnyb + 1, cyb, 0, ((i == x1 || i == x2) ? (0) : (r2)), 0); // Between their and our floor
                    ybottom[i] = clamp(min(cyb, cnyb), 0, ybottom[i]); // Shrink the remaining window above these floors
                }
                else
                {
                    /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                    unsigned r = (unsigned)0x010101 * (255-z);
                    line(game->surface, i, cya, cyb, 0, ((i == x1 || i == x2) ? (0) : (r)), 0);
                }
            }

            /* Schedule the neighboring sector for rendering within the window formed by this wall. */
            if(neighbor >= 0 && endx >= beginx && (head+MaxQueue+1-tail)%MaxQueue)
            {
                *head = (Item) { neighbor, beginx, endx };
                if(++head == queue+MaxQueue) head = queue;
            }
        }
        // for s in sector's edges
        ++rendSects[curr.secNo];
    } while(head != tail); // render any other queued sectors
}