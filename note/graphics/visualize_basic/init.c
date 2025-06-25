/* init.c
- init data (t_data, t_player, t_map)
- init pointers related to windowa -> save to t_data
*/

#include "main.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2; // x.y: Center of screen
	player->size = 10;
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D_window");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_len, &data->endian);

	//ver1
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		printf("Error: malloc failed");
		exit(1);
	}
	init_player(data->player);
	data->map = malloc(sizeof(t_map));
	if( !data->map)
	{
		free(data->player);
		printf("Error: malloc failed");
		exit(1);
	}

	//ver2: lazy init
	data->player = NULL;
	data->map = NULL;
}

void	clear_screen(t_data *data)
{
	int x;
	int y = 0;

	while(y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			data->addr[y * (data->line_len / 4) + x] = 0x00000000; // Black color
			x++;
		}
		y++;
	}
}

void	update_display(t_data *data)
{
	clear_screen(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->player);
	exit(0);
	return (0);
}
