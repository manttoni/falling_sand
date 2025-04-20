#include "../include/pixel.h"
#include "../include/settings.h"
#include <stdlib.h>

uint32_t pixel(unsigned int density, unsigned int velocity_x, unsigned int velocity_y, pixel_type type)
{
    return density << 24 | (velocity_x + 127) << 16 | (velocity_y + 127) << 8 | type;
}

char *pixel_to_string(uint32_t pixel)
{
    pixel_type type = pixel & PIXEL_TYPE_MASK;
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

void set_Y_velocity(uint32_t *pixel, int velocity)
{
    if (abs(velocity) >= 128)
        return;
    *pixel &= ~VELOCITY_Y_MASK;
    *pixel |= (velocity + 127) << 8;
}

void set_X_velocity(uint32_t *pixel, int velocity)
{
    if (abs(velocity) >= 128)
        return;
    *pixel &= ~VELOCITY_X_MASK;
    *pixel |= (velocity + 127) << 16;
}

int get_Y_velocity(uint32_t pixel)
{
    return ((pixel & VELOCITY_Y_MASK) >> 8) - 127;
}

int get_X_velocity(uint32_t pixel)
{
    return ((pixel & VELOCITY_X_MASK) >> 16) - 127;
}

void change_Y_velocity(uint32_t *pixel, int increment)
{
    set_Y_velocity(pixel, get_Y_velocity(*pixel) + increment);
}

void change_X_velocity(uint32_t *pixel, int increment)
{
    set_X_velocity(pixel, get_X_velocity(*pixel) + increment);
}

uint32_t *get_pixel(uint32_t *pixels, int x, int y)
{
    if (y * Y + x > X * Y || x < 0 || y < 0)
        return NULL;
    return &pixels[y * Y + x];
}

pixel_type get_pixel_type(uint32_t pixel)
{
    return pixel & PIXEL_TYPE_MASK;
}

void set_density(uint32_t *pixel, unsigned int density)
{
    if (density >= 256)
        return;
    *pixel &= ~DENSITY_MASK;
    *pixel |= density << 24;
}

int get_density(uint32_t pixel)
{
    return ((pixel & DENSITY_MASK) >> 24);
}

int get_mass(uint32_t pixel)
{
    return get_pixel_type(pixel) * get_density(pixel);
}

int row(int i)
{
    return i / X;
}

int col(int i)
{
    return i % X;
}

uint32_t get_pixel_color(uint32_t pixel)
{
    pixel_type type = pixel & PIXEL_TYPE_MASK;
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

t_neighbors get_neighbors(uint32_t *pixels, int i)
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
    if (nei.up != NULL && *nei.up == (uint32_t)type)
        return type;
    if (nei.down != NULL && *nei.down == (uint32_t)type)
        return type;
    if (nei.left != NULL && *nei.left == (uint32_t)type)
        return type;
    if (nei.right != NULL && *nei.right == (uint32_t)type)
        return type;
    return VOID;
}

bool is_liquid(uint32_t pixel)
{
    pixel_type type = pixel & PIXEL_TYPE_MASK;
    return type == WATER || type == OIL;
}

bool is_gas(uint32_t pixel)
{
    pixel_type type = pixel & PIXEL_TYPE_MASK;
    return type == VOID;
}

bool is_flowing(uint32_t pixel)
{
    pixel_type type = pixel & PIXEL_TYPE_MASK;
    return is_liquid(type) || is_gas(type);
}