/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:43:10 by albermud          #+#    #+#             */
/*   Updated: 2025/06/29 17:46:46 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / data->map_s;
	map_y = y / data->map_s;
	if (map_x < 0 || map_x >= data->map_width || map_y < 0
		|| map_y >= data->map_height)
		return (1);
	return (data->map[map_y * data->map_width + map_x]);
}

void	draw_map_2d(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (data->map[y * data->map_width + x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x333333;
			draw_cell(data, x, y, color);
		}
	}
}
