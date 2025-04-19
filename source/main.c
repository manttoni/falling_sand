#include "../include/data.h"
#include "../include/utils.h"
#include "../include/input.h"
#include "../include/simulation.h"
#include <stdio.h>

int start(t_data *data)
{
	mlx_key_hook(data->mlx, &keypress, data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		log_message(FAILURE, "mlx_image_to_window failure");
		return 1;
	}
	mlx_loop_hook(data->mlx, &mouse, data);
	mlx_loop_hook(data->mlx, &simulate, data);
	mlx_scroll_hook(data->mlx, &scroll, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return 0;
}

int main(void)
{
	t_data *data = init_data();
	if (data == NULL)
		log_message(FAILURE, "Data initialization failed");
	int ret = start(data);
	free_data(data);
	return ret;
}
