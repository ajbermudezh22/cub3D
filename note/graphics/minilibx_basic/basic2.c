#include "basic1.h"
#include <mlx.h>
#include <math.h>
#define PI 3.1416

int mapX = 8, mapY = 8, mapS = 64;
int map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,0,0,0,0,0,1,
	1,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1
};

void	init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D_window");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_len, &data->endian);

	data->player_dx = cos(data->player_angle);
	data->player_dy = cos(data->player_angle);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	
	dst = (char *)data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_map(t_data *data)
{
    int x, y, cell_size, color;
    int px, py, cell_y, cell_x;

    cell_size = 64;
    y = 0;
    while (y < mapY)
    {
        x = 0;
        while (x < mapX)
        {
            color = (map[y * mapX + x] == 1) ? 0xFFFFFF : 0x333333;
            px = x * cell_size;
            py = y * cell_size;
            cell_y = py;
            while (cell_y < py + cell_size)
            {
                cell_x = px;
                while (cell_x < px + cell_size)
                {
                    if (cell_x < WIDTH && cell_y < HEIGHT)
                    {
                        // Add brick pattern only to white walls
                        if (map[y * mapX + x] == 1)
                        {
                            // Horizontal lines every 16 pixels
                            if (cell_y % 16 == 0)
                                my_mlx_pixel_put(data, cell_x, cell_y, 0x808080);
                            // Vertical lines every 32 pixels, offset every other row
                            else if (cell_x % 32 == ((cell_y / 16 % 2) * 16))
                                my_mlx_pixel_put(data, cell_x, cell_y, 0x808080);
                            else
                                my_mlx_pixel_put(data, cell_x, cell_y, color);
                        }
                        else
                            my_mlx_pixel_put(data, cell_x, cell_y, color);
                    }
                    cell_x++;
                }
                cell_y++;
            }
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void draw_player(t_data *data, int player_x, int player_y)
{
	int	x;
	int	y;
	int	size;
	int	line_length;
	int	end_x;
	int	end_y;
	float	dx;
	float	dy;
	float	step;

	size = 10;
	y = player_y - size / 2;
	line_length = 20;
	while (y < player_y + size / 2)
	{
		x = player_x - size / 2;
		while (x < player_x + size / 2)
		{
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				my_mlx_pixel_put(data, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
	end_x = player_x + cos(data->player_angle) * line_length;
	end_y = player_y + sin(data->player_angle) * line_length;
	x = player_x;
	y = player_y;
	dx = end_x - player_x;
	dy = end_y - player_y;
	step = fmax(fabs(dx), fabs(dy));
	dx /= step;
	dy /= step;

	while (step-- > 0)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			my_mlx_pixel_put(data, x, y, 0xFF0000);
		x += dx;
		y += dy;
	}

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	clear_window(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0x808080);
			x++;
		}
		y++;
	}
}

int	is_wall(int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / mapS;
	map_y = y / mapS;

	if (map_x < 0 || map_x >= mapX || map_y < 0 || map_y >= mapY)
		return 1;
	return map[map_y * mapX + map_x];
}

int	key_hook(int keycode, t_data *data)
{
	int	move_speed;
	float	target_angle;
	int	new_x;
	int	new_y;

	move_speed = 10;
	target_angle = data->player_angle;
	new_x = data->player_x;
	new_y = data->player_y;
	if (keycode == 'w' || keycode == 'W')
	{
		new_y -= move_speed;
		target_angle += - PI / 2.0;
	}
	if (keycode == 's' || keycode == 'S')
	{
		new_y += move_speed;
		target_angle -= PI / 2.0;
	}
	if (keycode == 'a' || keycode == 'A')
	{
		new_x -= move_speed;
		target_angle = - PI;
	}	
	if (keycode == 'd' || keycode == 'D')
	{
		new_x += move_speed;
		target_angle = 0;
	}

	if ((new_x != data->player_x || new_y != data->player_y)
        && new_x >= 0 && new_x < WIDTH && new_y >= 0 && new_y < HEIGHT)
	{
		if (!is_wall(new_x, new_y))
		{
			data->player_x = new_x;
			data->player_y = new_y;
			data->player_angle = target_angle;
		}
	}
	clear_window(data);
	draw_map(data);
	draw_player(data, data->player_x, data->player_y);
	return (0);
}

int main()
{
	t_data	img;
	
	init(&img);
	img.player_x = WIDTH / 2;
	img.player_y = HEIGHT / 2;
	img.player_angle = 0;
	clear_window(&img);
	draw_map(&img);
	draw_player(&img, img.player_x, img.player_y);
	mlx_hook(img.win, 2, 1L<<0, key_hook, &img);
	mlx_loop(img.mlx);
	return (0);
}