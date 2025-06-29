/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:11 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 14:03:05 by albbermu         ###   ########.fr       */
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

void	setup_map_from_config(t_data *data)
{
	data->map.width = data->config.map_width;
	data->map.height = data->config.map_height;
	data->map.tile_size = 24;
	allocate_map_grid(data);
	fill_map_grid(data);
	setup_player_position(data);
}

int	is_wall_with_buffer(t_data *data, float x, float y, float buffer)
{
	t_buffer_check	check;

	check.min_x = (int)((x - buffer) / data->map.tile_size);
	check.max_x = (int)((x + buffer) / data->map.tile_size);
	check.min_y = (int)((y - buffer) / data->map.tile_size);
	check.max_y = (int)((y + buffer) / data->map.tile_size);
	if (check_buffer_bounds(data, &check))
		return (1);
	return (check_buffer_walls(data, &check));
}
