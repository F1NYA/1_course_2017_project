//
// Created by George Kobelev on 6/27/17.
//
#include <data_loader.h>
#include <macros.h>

void uploadData(Game * game) {
    //Sector * sectors = game->sectors;
    //int NumSectors = game->sectornum;
    FILE* fp = fopen("map.txt", "rt");
    if(!fp) {
        perror("map.txt");
        exit(EXIT_FAILURE);
    }
    char Buf[256], word[256], *ptr;
    XY* vert = NULL, v;
    int NumVertices = 0;
    unsigned n, m;
    while(fgets(Buf, sizeof(Buf), fp)) {
        switch (sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0') {
            case 'v': {// vertex
                for (sscanf(ptr += n, "%lf%n", &v.y, &n); sscanf(ptr += n, "%lf%n", &v.x, &n) == 1;) {
                    vert = (XY *) realloc(vert, ++NumVertices * sizeof(XY));
                    vert[NumVertices - 1] = v;
                }
                break;
            }
            case 's': {// sector
                game->sectors = (Sector *) realloc(game->sectors, ++game->numSectors * sizeof(*(game->sectors)));
                Sector *sect = &(game->sectors)[game->numSectors - 1];
                int *num = NULL;
                sscanf(ptr += n, "%lf%lf%n", &sect->floor, &sect->ceil, &n);
                for (m = 0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#';) {
                    num = (int *) realloc(num, ++m * sizeof(*num));
                    num[m - 1] = ((word[0] == 'x') ? (-1) : (atoi(word)));
                }
                sect->npoints = (m /= 2);
                sect->neighbors = (signed char *) malloc((m) * sizeof(*sect->neighbors));
                sect->vertex = (XY *) malloc((m + 1) * sizeof(*sect->vertex));

                for (n = 0; n < m; ++n) {
                    sect->neighbors[n] = num[m + n];
                }
                for (n = 0; n < m; ++n) {
                    sect->vertex[n + 1] = vert[num[n]];
                }
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
                free(num);
                break;
            }
            case 'p': {// player

                double angle;
                sscanf(ptr += n, "%lf %lf %lf %d", &v.x, &v.y, &angle, &n);
                game->player = (Player) {
                        {v.x, v.y, 0},
                        {0, 0, 0},
                        angle, 0, 0, 0, n};
                game->player.where.z = (game->sectors)[game->player.sector].floor + EyeH;
            }
        }
    }

    fclose(fp);
    free(vert);
}

void unloadData(Game * game) {
    for(unsigned a = 0; a < game->numSectors; ++a) {
        free(game->sectors[a].vertex);
    }
    for(unsigned a = 0; a < game->numSectors; ++a) {
        free(game->sectors[a].neighbors);
    }
    free(game->sectors);
    game->sectors    = NULL;
    game->numSectors = 0;
}
