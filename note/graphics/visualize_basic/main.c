#include "main.h"


void	free_2d_array(char **arr)
{
	//ACCESS TO NULL POINTER -> seg fault
	if (!arr)
		return ; 
	int i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	clean_exit(t_data *data, int exit_code)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->player)
		free(data->player);
	if (data->map)
	{
		if (data->map->grid)
			free_2d_array(data->map->grid);
		free(data->map);
	}
	exit(exit_code);
}

int main(int ac, char **av)
{
	(void)av[1]
	t_data	data;

	if (ac != 2)
		return (printf("Error: enter a map(.cub)!\n"), 1);

	//part1
	init_window(&data);

	// if (!load_map(&data, av[1]))
	// 	return (printf("Error: failed to load map '%s'!\n", av[1]), 1);



		// to display the image from part2
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	//part3
	mlx_hook(data.win, 2, 1L<<0, key_press, &data); // setup even hook: Key pressed
	mlx_hook(data.win, 17, 0, close_window, &data); // setup even hook: Window close 
	mlx_loop(data.mlx);

	//part4
	return (0); 
}