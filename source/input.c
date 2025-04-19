#include "../include/input.h"
#include "../include/data.h"
#include "../include/brush.h"
#include "../include/pixel.h"
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

void mouse(void *param)
{
    t_data *data = (t_data *)param;
    int mouse_x, mouse_y;
    mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);

    if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT)
        && get_pixel(data->pixels, mouse_x, mouse_y) != NULL)
    {
        paint(data->pixels, data->brush, mouse_x, mouse_y);
    }
}

void keypress(mlx_key_data_t mlx_data, void *param)
{
    t_data *data = (t_data *)param;

    if (mlx_data.key == MLX_KEY_ESCAPE)
    {
        mlx_close_window(data->mlx);
        return;
    }
}

void scroll(double xdelta, double ydelta, void *param)
{
    (void)xdelta;
    t_data *data = (t_data *)param;

    if (ydelta > 0)
        select_next_type(data->brush);
    else if (ydelta < 0)
        select_previous_type(data->brush);
    else
        return;

    printf("Brush type selected: %s\n", pixel_to_string(data->brush->type));
}