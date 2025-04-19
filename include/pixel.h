#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <stdbool.h>

typedef enum pixel_type
{
    VOID = 0,
    OIL,
    WATER,
    SAND,
    MUD,
    END
}   pixel_type;

typedef struct s_neighbors
{
    int *up;
    int *down;
    int *left;
    int *right;
}   t_neighbors;

char        *pixel_to_string(pixel_type type);
int         *get_pixel(int *pixels, int x, int y);
uint32_t    get_pixel_color(pixel_type type);
t_neighbors get_neighbors(int *pixels, int i);
pixel_type  neighboring(t_neighbors nei, pixel_type type);
bool        is_liquid(pixel_type type);

#endif