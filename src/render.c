//
// Created by George Kobelev on 5/11/17.
//

#include <render.h>
#include <macros.h>


#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

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

#define Yaw(y,z) (y + z*player.yaw)

SDL_Surface *surface = NULL;

void LoadData()
{
    FILE* fp = fopen("map-clear.txt", "rt");
    if(!fp)
    {
        perror("map-clear.txt");
        exit(1);
    }
    char Buf[256], word[256], *ptr;
    struct xy* vert = NULL, v;
    int NumVertices = 0;
    unsigned int n, m;
    while(fgets(Buf, sizeof(Buf), fp))
        ptr = Buf;
        switch(sscanf(ptr, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
                for ( sscanf(ptr += n, "%lf%n", &v.y, &n); sscanf(ptr += n, "%lf%n", &v.x, &n) == 1; )
                {
                    vert = realloc(vert, ++NumVertices * sizeof(*vert));
                    vert[NumVertices-1] = v;
                }
                break;

            case 's': // sector
                sectors = realloc(sectors, ++NumSectors * sizeof(*sectors));
                struct sector* sect = &sectors[NumSectors-1];
                int* num = NULL;
                sscanf(ptr += n, "%lf%lf%n", &sect->floor, &sect->ceil, &n);
                for(m = 0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
                {
                    num = realloc(num, ++m * sizeof(*num));
                    num[m-1] = ( (word[0]=='x') ? (-1) : (atoi(word)));
                }
                sect->npoints   = (m /= 2);
                sect->neighbors = malloc( (m)   * sizeof(*sect->neighbors) );
                sect->vertex    = malloc( (m+1) * sizeof(*sect->vertex)    );
                for(n = 0; n < m; ++n)
                {
                    sect->neighbors[n] = num[m + n];
                }
                for(n = 0; n < m; ++n)
                {
                    sect->vertex[n + 1] = vert[num[n]]; // TODO: Range checking
                }
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
                free(num);
                break;

            case 'p':; // player
                float angle;
                sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
                player = (struct player) {
                        {v.x, v.y, 0},
                        {0,0,0},
                        angle,0,0,0, n }; // TODO: Range checking
                player.where.z = sectors[player.sector].floor + EyeHeight;
        }
    fclose(fp);
    free(vert);
}

void UnloadData()
{
    for(unsigned a = 0; a < NumSectors; ++a)
    {
        free(sectors[a].vertex);
    }
    for(unsigned a = 0; a < NumSectors; ++a)
    {
        free(sectors[a].neighbors);
    }
    free(sectors);
    sectors    = NULL;
    NumSectors = 0;
}

void vline(int x, int y1, int y2, int top, int middle, int bottom)
{
    int *pix = (int*) surface->pixels;
    y1 = clamp(y1, 0, H-1);
    y2 = clamp(y2, 0, H-1);
    if(y2 == y1)
        pix[y1*W+x] = middle;
    else if(y2 > y1)
    {
        pix[y1*W+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*W+x] = middle;
        pix[y2*W+x] = bottom;
    }
}

void MovePlayer(double dx, double dy)
{
    double px = player.where.x, py = player.where.y;
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    const struct sector* const sect = &sectors[player.sector];
    const struct xy* const vert = sect->vertex;
    for(unsigned s = 0; s < (sect->npoints); ++s)
        if(sect->neighbors[s] >= 0
           && IntersectBox(px, py, px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
           && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            player.sector = sect->neighbors[s];
            break;
        }

    player.where.x += dx;
    player.where.y += dy;
    player.anglesin = sinf((float)player.angle);
    player.anglecos = cosf((float)player.angle);
}

void DrawScreen()
{
    enum { MaxQueue = 32 };  // maximum number of pending portal renders
    Item queue[MaxQueue], *head = queue, *tail = queue;
    int ytop[W] = {0}, ybottom[W], renderedsectors[NumSectors];
    for(unsigned x = 0; x < W; ++x) ybottom[x] = H-1;
    for(unsigned n = 0; n < NumSectors; ++n) renderedsectors[n] = 0;

    /* Begin whole-screen rendering from where the player is. */
    *head = (Item) { player.sector, 0, W-1 };

    if(++head == queue+MaxQueue) head = queue;

    do {
        /* Pick a sector & slice from the queue to draw */
        const Item now = *tail;
        if(++tail == queue+MaxQueue) tail = queue;

        if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
        ++renderedsectors[now.sectorno];
        const Sector* const sect = &sectors[now.sectorno];
        /* Render each wall of this sector that is facing towards player. */
        for(unsigned s = 0; s < sect->npoints; ++s)
        {
            /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
            double vx1 = sect->vertex[s+0].x - player.where.x, vy1 = sect->vertex[s+0].y - player.where.y;
            double vx2 = sect->vertex[s+1].x - player.where.x, vy2 = sect->vertex[s+1].y - player.where.y;
            /* Rotate them around the player's view */
            double pcos = player.anglecos, psin = player.anglesin;
            double tx1 = vx1 * psin - vy1 * pcos,  tz1 = vx1 * pcos + vy1 * psin;
            double tx2 = vx2 * psin - vy2 * pcos,  tz2 = vx2 * pcos + vy2 * psin;
            /* Is the wall at least partially in front of the player? */
            if(tz1 <= 0 && tz2 <= 0) continue;
            /* If it's partially behind the player, clip it against player's view frustrum */
            if(tz1 <= 0 || tz2 <= 0)
            {
                double nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
                // Find an intersection between the wall and the approximate edges of player's view
                XY i1 = Intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside,farz);
                XY i2 = Intersect(tx1,tz1,tx2,tz2,  nearside,nearz,  farside,farz);
                if(tz1 < nearz)
                {
                    if(i1.y > 0)
                    {
                        tx1 = i1.x;
                        tz1 = i1.y;
                    }
                    else
                    {
                        tx1 = i2.x;
                        tz1 = i2.y;
                    }
                }
                if(tz2 < nearz)
                {
                    if(i1.y > 0)
                    {
                        tx2 = i1.x;
                        tz2 = i1.y;
                    }
                    else {
                        tx2 = i2.x;
                        tz2 = i2.y;
                    }
                }
            }
            /* Do perspective transformation */
            double xscale1 = hfov / tz1, yscale1 = vfov / tz1;    int x1 = W/2 - (int)(tx1 * xscale1);
            double xscale2 = hfov / tz2, yscale2 = vfov / tz2;    int x2 = W/2 - (int)(tx2 * xscale2);
            if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue; // Only render if it's visible
            /* Acquire the floor and ceiling heights, relative to where the player's view is */
            double yceil  = sect->ceil  - player.where.z;
            double yfloor = sect->floor - player.where.z;
            /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
            int neighbor = sect->neighbors[s];
            double nyceil = 0, nyfloor = 0;
            if(neighbor >= 0) // Is another sector showing through this portal?
            {
                nyceil  = sectors[neighbor].ceil  - player.where.z;
                nyfloor = sectors[neighbor].floor - player.where.z;
            }
            /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */

            int y1a  = H/2 - (int)(Yaw(yceil, tz1) * yscale1),  y1b = H/2 - (int)(Yaw(yfloor, tz1) * yscale1);
            int y2a  = H/2 - (int)(Yaw(yceil, tz2) * yscale2),  y2b = H/2 - (int)(Yaw(yfloor, tz2) * yscale2);
            /* The same for the neighboring sector */
            int ny1a = H/2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = H/2 - (int)(Yaw(nyfloor, tz1) * yscale1);
            int ny2a = H/2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = H/2 - (int)(Yaw(nyfloor, tz2) * yscale2);

            /* Render the wall. */
            int beginx = max(x1, now.sx1), endx = min(x2, now.sx2);
            for(int x = beginx; x <= endx; ++x)
            {
                /* Calculate the Z coordinate for this point. (Only used for lighting.) */
                int z = (int)((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
                /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
                int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[x],ybottom[x]); // top
                int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[x],ybottom[x]); // bottom

                /* Render ceiling: everything above this sector's ceiling height. */
                vline(x, ytop[x], cya-1, 0x111111 ,0x222222,0x111111);
                /* Render floor: everything below this sector's floor height. */
                vline(x, cyb+1, ybottom[x], 0x0000FF,0x0000AA,0x0000FF);

                /* Is there another sector behind this edge? */
                if(neighbor >= 0)
                {
                    /* Same for _their_ floor and ceiling */
                    int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a, cnya = clamp(nya, ytop[x],ybottom[x]);
                    int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b, cnyb = clamp(nyb, ytop[x],ybottom[x]);
                    /* If our ceiling is higher than their ceiling, render upper wall */
                    unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
                    vline(x, cya, cnya-1, 0, ((x == x1 || x == x2) ? (0) : (r1)), 0); // Between our and their ceiling
                    ytop[x] = clamp(max(cya, cnya), ytop[x], H-1);   // Shrink the remaining window below these ceilings
                    /* If our floor is lower than their floor, render bottom wall */
                    vline(x, cnyb+1, cyb, 0, ((x == x1 || x == x2) ? (0) : (r2)), 0); // Between their and our floor
                    ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
                }
                else
                {
                    /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                    unsigned r = 0x010101 * (255-z);
                    vline(x, cya, cyb, 0, ((x == x1 || x == x2) ? (0) : (r)), 0);
                }
            }
            /* Schedule the neighboring sector for rendering within the window formed by this wall. */
            if(neighbor >= 0 && endx >= beginx && (head+MaxQueue+1-tail)%MaxQueue)
            {
                *head = (Item) { neighbor, beginx, endx };
                if(++head == queue+MaxQueue)
                {
                    head = queue;
                }
            }
        } // for s in sector's edges
        ++renderedsectors[now.sectorno];
    } while(head != tail); // render any other queued sectors
}


