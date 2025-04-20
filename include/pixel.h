#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <stdbool.h>

#define PIXEL_TYPE_MASK 0xFF
#define VELOCITY_Y_MASK 0xFF00
#define VELOCITY_X_MASK 0xFF0000
#define DENSITY_MASK    0xFF000000

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
    uint32_t *up;
    uint32_t *down;
    uint32_t *left;
    uint32_t *right;
}   t_neighbors;

char        *pixel_to_string(uint32_t pixel);
uint32_t    *get_pixel(uint32_t *pixels, int x, int y);
uint32_t    get_pixel_color(uint32_t pixel);
t_neighbors get_neighbors(uint32_t *pixels, int i);
pixel_type  neighboring(t_neighbors nei, pixel_type type);
bool        is_liquid(uint32_t pixel);
bool        is_gas(uint32_t pixel);
bool        is_flowing(uint32_t pixel);
void        set_Y_velocity(uint32_t *pixel, int velocity);
void        set_X_velocity(uint32_t *pixel, int velocity);
int         get_Y_velocity(uint32_t pixel);
int         get_X_velocity(uint32_t pixel);
void        change_Y_velocity(uint32_t *pixel, int increment);
void        change_X_velocity(uint32_t *pixel, int increment);
pixel_type  get_pixel_type(uint32_t pixel);
int         get_density(uint32_t pixel);
int         get_mass(uint32_t pixel);
int         row(int i);
int         col(int i);
uint32_t    new_pixel(unsigned int density, unsigned int velocity_x, unsigned int velocity_y, pixel_type type);

#endif