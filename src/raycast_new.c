/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:23 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 14:57:42 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_wall_hit(t_data *data, float current_x, float current_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)current_x / data->map.tile_size;
	map_y = (int)current_y / data->map.tile_size;
	if (map_x >= 0 && map_x < data->map.width
		&& map_y >= 0 && map_y < data->map.height)
	{
		if (data->map.grid[map_y * data->map.width + map_x] == 1)
			return (1);
	}
	return (0);
}

static float	calculate_distance(t_data *data, float current_x, float current_y)
{
	return (sqrt(pow(current_x - data->player_x, 2)
			+ pow(current_y - data->player_y, 2)));
}

float	cast_ray_2d(t_data *data, float ray_angle, int *hit_x, int *hit_y)
{
	float	dx;
	float	dy;
	float	current_x;
	float	current_y;
	float	step_size;
	float	distance;
	float	angle_diff;

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
		{
			distance = calculate_distance(data, current_x, current_y);
			angle_diff = ray_angle - data->player_angle;
			*hit_x = (int)current_x;
			*hit_y = (int)current_y;
			return (distance * cos(angle_diff));
		}
	}
	*hit_x = (int)current_x;
	*hit_y = (int)current_y;
	distance = calculate_distance(data, current_x, current_y);
	angle_diff = ray_angle - data->player_angle;
	return (distance * cos(angle_diff));
}
