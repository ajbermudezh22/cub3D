/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:11 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/29 18:03:02 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	data->player_x = data->config.player_x * data->map_s + data->map_s / 2;
	data->player_y = data->config.player_y * data->map_s + data->map_s / 2;
	data->player_angle = get_player_angle(data->config.player_dir);
	data->player_dx = cos(data->player_angle);
	data->player_dy = sin(data->player_angle);
}

static void	init_map_data(t_data *data)
{
	data->map_width = data->config.map_width;
	data->map_height = data->config.map_height;
	data->map_s = 24;
	if (data->map)
		free(data->map);
	data->map = malloc(data->map_width * data->map_height * sizeof(int));
	if (!data->map)
	{
		printf("Error: Failed to allocate memory for map\n");
		exit(1);
	}
}

void	setup_map_from_config(t_data *data)
{
	int	x;
	int	y;

	init_map_data(data);
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (data->config.map_grid[y][x] == '1')
				data->map[y * data->map_width + x] = 1;
			else
				data->map[y * data->map_width + x] = 0;
		}
	}
	setup_player_position(data);
}

void	draw_cell(t_data *data, int x, int y, int color)
{
	int	cell_x;
	int	cell_y;
	int	px;
	int	py;

	px = x * data->map_s;
	py = y * data->map_s;
	if (px >= MAP_WIDTH || py >= HEIGHT)
		return ;
	cell_y = py - 1;
	while (++cell_y < py + data->map_s && cell_y < HEIGHT)
	{
		cell_x = px - 1;
		while (++cell_x < px + data->map_s && cell_x < MAP_WIDTH)
		{
			if (cell_x == px || cell_y == py)
				my_mlx_pixel_put(data, cell_x, cell_y, 0x666666);
			else
				my_mlx_pixel_put(data, cell_x, cell_y, color);
		}
	}
}
