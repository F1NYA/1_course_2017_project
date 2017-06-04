//
// Created by George Kobelev on 6/4/17.
//

#ifndef PROGBASE3_MACROSES_H
#define PROGBASE3_MACROSES_H

#undef max
#undef min
#undef clamp

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

#define clamp(a, mi,ma)      min(max(a,mi),ma)


#define W 608
#define H 480

#define EyeHeight  6
#define DuckHeight 2.5
#define HeadMargin 1
#define KneeHeight 2
#define hfov (0.73f*H)
#define vfov (.2f*H)

#endif //PROGBASE3_MACROSES_H
