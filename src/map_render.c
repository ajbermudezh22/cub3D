/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:00:00 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/29 10:00:00 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_cell(t_data *data, int x, int y, int color)
{
	int	cell_x;
	int	cell_y;
	int	px;
	int	py;

	px = x * data->map.tile_size;
	py = y * data->map.tile_size;
	if (px >= MAP_WIDTH || py >= HEIGHT)
		return ;
	cell_y = py - 1;
	while (++cell_y < py + data->map.tile_size && cell_y < HEIGHT)
	{
		cell_x = px - 1;
		while (++cell_x < px + data->map.tile_size && cell_x < MAP_WIDTH)
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
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			if (data->map.grid[y * data->map.width + x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x333333;
			draw_cell(data, x, y, color);
		}
	}
}

void	setup_player_position(t_data *data)
{
	data->map_width = data->map.width;
	data->map_height = data->map.height;
	data->player_x = data->config.player_x * data->map.tile_size
		+ data->map.tile_size / 2;
	data->player_y = data->config.player_y * data->map.tile_size
		+ data->map.tile_size / 2;
	data->player_angle = get_player_angle(data->config.player_dir);
	data->player_dx = cos(data->player_angle);
	data->player_dy = sin(data->player_angle);
}

int	is_wall(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / data->map.tile_size;
	map_y = y / data->map.tile_size;
	if (map_x < 0 || map_x >= data->map.width
		|| map_y < 0 || map_y >= data->map.height)
		return (1);
	return (data->map.grid[map_y * data->map.width + map_x]);
}
