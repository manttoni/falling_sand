#ifndef INPUT_H
#define INPUT_H

#include "../lib/MLX42/include/MLX42/MLX42.h"

void    keypress(mlx_key_data_t mlx_data, void *param);
void    mouse(void *param);
void    scroll(double xdelta, double ydelta, void *param);

#endif