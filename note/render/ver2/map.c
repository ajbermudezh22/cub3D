#include "map.h"
#include <math.h>
#include <stdlib.h>

#define PI 3.141592

// Global variables for map
int mapX, mapY, mapS = 24;
int *map = NULL;

float	get_player_angle(char dir)
{
	if (dir == 'N')
		return (3 * PI / 2);
	if (dir == 'S')
		return (PI / 2);
	if (dir == 'E')
		return (0);
	if (dir == 'W')
		return (PI);
	return (0);
}

static void	setup_player_position(t_data *data)
{
	data->map_width = mapX;
	data->map_height = mapY;
	data->player_x = data->config.player_x * mapS + mapS / 2;
	data->player_y = data->config.player_y * mapS + mapS / 2;
	data->player_angle = get_player_angle(data->config.player_dir);
	data->player_dx = cos(data->player_angle);
	data->player_dy = sin(data->player_angle);
}

void	setup_map_from_config(t_data *data)
{
	int	x;
	int	y;

	mapX = data->config.map_width;
	mapY = data->config.map_height;
	if (map)
		free(map);
	map = malloc(mapX * mapY * sizeof(int));
	if (!map)
	{
		printf("Error: Failed to allocate memory for map\n");
		exit(1);
	}
	y = -1;
	while (++y < mapY)
	{
		x = -1;
		while (++x < mapX)
		{
			if (data->config.map_grid[y][x] == '1')
				map[y * mapX + x] = 1;
			else
				map[y * mapX + x] = 0;
		}
	}
	setup_player_position(data);
}

static void	draw_cell(t_data *data, int x, int y, int color)
{
	int	cell_x;
	int	cell_y;
	int	px;
	int	py;

	px = x * mapS;
	py = y * mapS;
	if (px >= MAP_WIDTH || py >= HEIGHT)
		return ;
	cell_y = py - 1;
	while (++cell_y < py + mapS && cell_y < HEIGHT)
	{
		cell_x = px - 1;
		while (++cell_x < px + mapS && cell_x < MAP_WIDTH)
		{
			if (cell_x == px || cell_y == py)
				my_mlx_pixel_put(data, cell_x, cell_y, 0x666666);
			else
				my_mlx_pixel_put(data, cell_x, cell_y, color);
		}
	}
}

void	draw_map_2d(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < mapY)
	{
		x = -1;
		while (++x < mapX)
		{
			if (map[y * mapX + x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x333333;
			draw_cell(data, x, y, color);
		}
	}
}

int	is_wall(int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / mapS;
	map_y = y / mapS;
	if (map_x < 0 || map_x >= mapX || map_y < 0 || map_y >= mapY)
		return (1);
	return (map[map_y * mapX + map_x]);
}
