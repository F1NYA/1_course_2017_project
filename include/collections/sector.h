//
// Created by George Kobelev on 6/27/17.
//

#ifndef PROGBASE3_SECTOR_H
#define PROGBASE3_SECTOR_H

#include "vector.h"

/**
 * @brief Structure that is a representation of prism.
 * @struct Sector
 *
 */
typedef struct sector {
    double floor, ceil;
    XY *vertex;
    signed char *neighbors;
    unsigned int npoints;
}Sector;

#endif //PROGBASE3_SECTOR_H
