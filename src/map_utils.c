/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:00:00 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/29 10:00:00 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	allocate_map_grid(t_data *data)
{
	if (data->map.grid)
		free(data->map.grid);
	data->map.grid = malloc(data->map.width * data->map.height * sizeof(int));
	if (!data->map.grid)
		exit((printf("Error: Failed to allocate memory for map\n"), 1));
}

void	fill_map_grid(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			if (data->config.map_grid[y][x] == '1')
				data->map.grid[y * data->map.width + x] = 1;
			else
				data->map.grid[y * data->map.width + x] = 0;
		}
	}
}

int	check_buffer_bounds(t_data *data, t_buffer_check *check)
{
	if (check->min_x < 0 || check->max_x >= data->map.width
		|| check->min_y < 0 || check->max_y >= data->map.height)
		return (1);
	return (0);
}

int	check_buffer_walls(t_data *data, t_buffer_check *check)
{
	int	my;
	int	mx;

	my = check->min_y - 1;
	while (++my <= check->max_y)
	{
		mx = check->min_x - 1;
		while (++mx <= check->max_x)
		{
			if (data->map.grid[my * data->map.width + mx])
				return (1);
		}
	}
	return (0);
}
