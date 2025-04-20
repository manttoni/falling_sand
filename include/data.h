#ifndef DATA_H
#define DATA_H

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../include/brush.h"
#include "../include/settings.h"

typedef struct s_data
{
    mlx_t       *mlx;
    mlx_image_t *image;
    uint32_t    *pixels;
    t_brush     *brush;
    int         speed;
}   t_data;

t_data  *init_data();
void    free_data(t_data *data);

#endif