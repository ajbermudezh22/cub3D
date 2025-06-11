#include "move_upwards.h"
/* note

	this program allows user to move the player by pressing `w`

*/

void	update_display(t_data *data);

int key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == KEY_W) // Move up
	{
		data->player->y -= 5;
		if (data->player->y < 0)
			data->player->y = 0;
	}
	update_display(data);

	return 0;
}

void	draw_player(t_data *data)
{
	//loop through a square area around player center
	int radius = data->player->size / 2;
	int x = data->player->x - radius;
	int y = data->player->y - radius;

	while (y <= data->player->y + radius)
	{
		x = data->player->x - radius; 
		while (x <= data->player->x + radius)
		{
			//ver1:  circle equation: (x-h)² + (y-k)² ≤ r²
			/*if ((x - data->player->x) * (x - data->player->x) + (y - data->player->y) * (y - data->player->y) <= radius * radius &&
				x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				data->addr[y * (data->line_len / 4) + x] = 0x00FFFF00; // Yellow
			*/

			//ver2 : square
			if ( x <= data->player->x + radius && y <= data->player->y + radius && x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT )
				data->addr[y * (data->line_len / 4) + x] = 0x00FFFF00; // Yellow
			x++;
		}
		y++;
	}
}

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

	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		printf("Error: malloc failed");
		exit(1);
	}
	init_player(data->player);
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

int main()
{
	t_data	data;

	//part1
	init_window(&data);

		// to display the image from part2
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	//part3
	mlx_hook(data.win, 2, 1L<<0, key_press, &data); // setup even hook: Key pressed
	mlx_hook(data.win, 17, 0, close_window, &data); // setup even hook: Window close 
	mlx_loop(data.mlx);

	//part4
	return (0); 
}