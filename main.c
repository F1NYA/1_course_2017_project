//
// Created by George Kobelev on 4/10/17.
//

/// fibonachi - Recursive function.
/// @param x - Counter for returned number.
/// @return - Return x.

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <macros.h>
#include <game.h>
#include <data_loader.h>
#include <render.h>
#include <player_func.h>

int main(int argv, char ** argc) {

    Game game = {.surface = NULL, .sectors = NULL, .numSectors = 0};


    uploadData(&game);

    Sector* sect = &(game.sectors[0]);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *win = SDL_CreateWindow("MY KURSACH KEK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_FOREIGN | SDL_WINDOW_OPENGL);


    SDL_ShowCursor(SDL_DISABLE);

    int wsad[4]={0,0,0,0}, ground=0, falling=1, moving=0, ducking=0;
    double yaw = 0;

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    game.surface = SDL_CreateRGBSurface(0, W, H, 32, 0, 0, 0, 0);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, game.surface);



    while(1)
    {
        SDL_LockSurface(game.surface);
        DrawScreen(&game);
        SDL_UpdateTexture(tex, NULL, game.surface->pixels, game.surface->pitch);
        SDL_UnlockSurface(game.surface);

        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);

        /* Vertical collision detection */
        double eyeheight = ducking ? DuckHeight : EyeHeight;
        ground = !falling;
        if(falling)
        {
            game.player.velocity.z -= 0.05f; /* Add gravity */
            double nextz = game.player.where.z + game.player.velocity.z;
            int n = game.player.sector;
            Sector* sect = &(game.sectors)[0];
            if(game.player.velocity.z < 0 && nextz  < game.sectors[game.player.sector].floor + eyeheight) // When going down
            {
                /* Fix to ground */
                game.player.where.z    = game.sectors[game.player.sector].floor + eyeheight;
                game.player.velocity.z = 0;
                falling = 0;
                ground  = 1;
            }
            else if(game.player.velocity.z > 0 && nextz > game.sectors[game.player.sector].ceil) // When going up
            {
                /* Prevent jumping above ceiling */
                game.player.velocity.z = 0;
                falling = 1;
            }
            if(falling)
            {
                game.player.where.z += game.player.velocity.z;
                moving = 1;
            }
        }
        /* Horizontal collision detection */
        if(moving)
        {
            double px = game.player.where.x,    py = game.player.where.y;
            double dx = game.player.velocity.x, dy = game.player.velocity.y;

            const struct sector* const sect = &(game.sectors)[game.player.sector];
            const struct xy* const vert = sect->vertex;
            /* Check if the player is about to cross one of the sector's edges */
            for(unsigned s = 0; s < sect->npoints; ++s)
                if(IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
                   && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
                {
                    /* Check where the hole is. */
                    double hole_low  = sect->neighbors[s] < 0 ?  9e9 : max(sect->floor, game.sectors[sect->neighbors[s]].floor);
                    double hole_high = sect->neighbors[s] < 0 ? -9e9 : min(sect->ceil,  game.sectors[sect->neighbors[s]].ceil );
                    /* Check whether we're bumping into a wall. */
                    if(hole_high < game.player.where.z+HeadMargin
                       || hole_low  > game.player.where.z-eyeheight+KneeHeight)
                    {
                        /* Bumps into a wall! Slide along the wall. */
                        /* This formula is from Wikipedia article "vector projection". */
                        double xd = vert[s+1].x - vert[s+0].x, yd = vert[s+1].y - vert[s+0].y;
                        dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        moving = 0;
                    }
                }
            MovePlayer(&game,dx, dy);
            falling = 1;
        }

        SDL_Event ev;
        while(SDL_PollEvent(&ev))
            switch(ev.type)
            {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    switch(ev.key.keysym.sym)
                    {
                        case 'w': wsad[0] = ev.type==SDL_KEYDOWN; break;
                        case 's': wsad[1] = ev.type==SDL_KEYDOWN; break;
                        case 'a': wsad[2] = ev.type==SDL_KEYDOWN; break;
                        case 'd': wsad[3] = ev.type==SDL_KEYDOWN; break;
                        case 'q': goto done;
                        case ' ': /* jump */
                            if(ground) { game.player.velocity.z += 0.5; falling = 1; }
                            break;
                        case SDLK_LCTRL: /* duck */
                        case SDLK_RCTRL: ducking = ev.type==SDL_KEYDOWN; falling=1; break;
                        default: break;
                    }
                    break;
                case SDL_QUIT: goto done;
            }

        /* mouse aiming */
        int x,y;
        SDL_GetRelativeMouseState(&x,&y);
        //printf("%d, %d", x, y);
        game.player.angle += x * 0.03f;
        yaw          = clamp(yaw - y*0.05f, -5, 5);
        game.player.yaw   = yaw - game.player.velocity.z*0.5f;
        MovePlayer(&game,0,0);

        double move_vec[2] = {0.f, 0.f};
        if(wsad[0]) { move_vec[0] += game.player.anglecos*0.2f; move_vec[1] += game.player.anglesin*0.2f; }
        if(wsad[1]) { move_vec[0] -= game.player.anglecos*0.2f; move_vec[1] -= game.player.anglesin*0.2f; }
        if(wsad[2]) { move_vec[0] += game.player.anglesin*0.2f; move_vec[1] -= game.player.anglecos*0.2f; }
        if(wsad[3]) { move_vec[0] -= game.player.anglesin*0.2f; move_vec[1] += game.player.anglecos*0.2f; }
        int pushing = wsad[0] || wsad[1] || wsad[2] || wsad[3];
        double acceleration = pushing ? 0.4 : 0.2;

        game.player.velocity.x = game.player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
        game.player.velocity.y = game.player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

        if(pushing) moving = 1;

        SDL_Delay(10);
    }

    done:

    unloadData(&game);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}


