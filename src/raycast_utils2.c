/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:23 by albbermu          #+#    #+#             */
/*   Updated: 2025/07/05 08:19:55 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	cast_ray_2d(t_data *data, float ray_angle, int *hit_x, int *hit_y)
{
	float	dx;
	float	dy;
	float	current_x;
	float	current_y;
	float	step_size;

	dx = cos(ray_angle);
	dy = sin(ray_angle);
	current_x = data->player_x;
	current_y = data->player_y;
	step_size = 0.5;
	while (1)
	{
		current_x += dx * step_size;
		current_y += dy * step_size;
		if (current_x < 0 || current_x >= MAP_WIDTH
			|| current_y < 0 || current_y >= HEIGHT)
			break ;
		if (check_wall_hit(data, current_x, current_y))
			return (calculate_distance(data, current_x, current_y));
	}
	*hit_x = (int)current_x;
	*hit_y = (int)current_y;
	return (calculate_distance(data, current_x, current_y));
}

int	check_wall_hit(t_data *data, float current_x, float current_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)current_x / TILE_SIZE;
	map_y = (int)current_y / TILE_SIZE;
	if (map_x >= 0 && map_x < data->config.map_width
		&& map_y >= 0 && map_y < data->config.map_height)
	{
		if (data->config.map_grid[map_y][map_x] == '1')
			return (1);
	}
	return (0);
}

float	calculate_distance(t_data *data, float current_x, float current_y)
{
	return (sqrt(pow(current_x - data->player_x, 2)
			+ pow(current_y - data->player_y, 2)));
}

void	draw_ray_line(t_data *data, int hit_x, int hit_y, int color)
{
	t_line_iter	line;
	int			step;

	if (hit_x >= MAP_WIDTH)
		return ;
	line.dx = hit_x - data->player_x;
	line.dy = hit_y - data->player_y;
	line.steps = fmax(fabs(line.dx), fabs(line.dy));
	if (line.steps <= 0)
		return ;
	line.dx /= line.steps;
	line.dy /= line.steps;
	line.x = data->player_x;
	line.y = data->player_y;
	step = -1;
	while (++step < (int)line.steps && line.x < MAP_WIDTH)
	{
		my_mlx_pixel_put(data, (int)line.x, (int)line.y, color);
		line.x += line.dx;
		line.y += line.dy;
	}
}

void	draw_player_circle(t_data *data)
{
	int	size;
	int	x;
	int	y;
	int	px;
	int	py;

	size = 8;
	if (data->player_x >= MAP_WIDTH)
		return ;
	y = -size - 1;
	while (++y <= size)
	{
		x = -size - 1;
		while (++x <= size)
		{
			if (x * x + y * y <= size * size)
			{
				px = data->player_x + x;
				py = data->player_y + y;
				if (px < MAP_WIDTH)
					my_mlx_pixel_put(data, px, py, 0xFFFF00);
			}
		}
	}
}
