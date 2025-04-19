#include "../include/pixel.h"
#include "../include/settings.h"
#include <stdlib.h>

char *pixel_to_string(pixel_type type)
{
    switch(type)
    {
        case SAND:
            return "SAND";
        case WATER:
            return "WATER";
        case MUD:
            return "MUD";
        case OIL:
            return "OIL";
        default:
            return "ERASER";
    }
}

int *get_pixel(int *pixels, int x, int y)
{
    if (y * Y + x > X * Y || x < 0 || y < 0)
        return NULL;
    return &pixels[y * Y + x];
}

uint32_t get_pixel_color(pixel_type type)
{
    switch(type)
    {
        case SAND:
            return SAND_COLOR;
        case WATER:
            return WATER_COLOR;
        case MUD:
            return MUD_COLOR;
        case OIL:
            return OIL_COLOR;
        default:
            return BACKGROUND_COLOR;
    }
}

t_neighbors get_neighbors(int *pixels, int i)
{
    t_neighbors neighbors;

    neighbors.up =      i - X < 0       ? NULL : &pixels[i - X];
    neighbors.down =    i + X > X * Y   ? NULL : &pixels[i + X];
    neighbors.left =    i % X == 0      ? NULL : &pixels[i - 1];
    neighbors.right =   i % X == X - 1  ? NULL : &pixels[i + 1];

    return neighbors;
}

pixel_type neighboring(t_neighbors nei, pixel_type type)
{
    if (nei.up != NULL && *nei.up == (int)type)
        return type;
    if (nei.down != NULL && *nei.down == (int)type)
        return type;
    if (nei.left != NULL && *nei.left == (int)type)
        return type;
    if (nei.right != NULL && *nei.right == (int)type)
        return type;
    return VOID;
}

bool is_liquid(pixel_type type)
{
    return type == WATER || type == OIL;
}