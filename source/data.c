#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../include/data.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>

t_data *init_data()
{
    t_data *data = malloc(sizeof(t_data));
    if (data == NULL)
	{
        log_message(FAILURE, "Malloc failed");
		return NULL;
	}
	bzero(data, sizeof(t_data));
	data->speed = 2;

	// mlx stuff
	data->mlx = mlx_init(X, Y, "Pixelator", true);
    if (data->mlx == NULL)
	{
		free_data(data);
		log_message(FAILURE, "mlx_init failed");
        return NULL;
	}

	data->image = mlx_new_image(data->mlx, X, Y);
    if (data->image == NULL)
	{
		free_data(data);
		log_message(FAILURE, "mlx_new_image failed");
        return NULL;
	}
	memset(data->image->pixels, BACKGROUND_COLOR, X * Y * sizeof(int));

	// non-mlx stuff
	data->pixels = malloc(X * Y * sizeof(int));
	if (data->pixels == NULL)
	{
		free_data(data);
		log_message(FAILURE, "malloc failed");
		return NULL;
	}
	memset(data->pixels, VOID, X * Y * sizeof(int));

	data->brush = malloc(sizeof(t_brush));
	if (data->brush == NULL)
	{
		free_data(data);
		log_message(FAILURE, "malloc failed");
		return NULL;
	}
	data->brush->size = 10;
	data->brush->type = SAND;

	return data;
}

void free_data(t_data *data)
{
	free(data->brush);
	free(data->pixels);
    free(data);
}