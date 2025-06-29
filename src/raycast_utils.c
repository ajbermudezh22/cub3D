/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:07:05 by albermud          #+#    #+#             */
/*   Updated: 2025/06/29 19:07:23 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_hit_point(t_data *data, int hit_x, int hit_y)
{
	if (hit_x >= MAP_WIDTH)
		return ;
	my_mlx_pixel_put(data, hit_x, hit_y, 0xFF0000);
	my_mlx_pixel_put(data, hit_x - 1, hit_y, 0xFF0000);
	my_mlx_pixel_put(data, hit_x + 1, hit_y, 0xFF0000);
	my_mlx_pixel_put(data, hit_x, hit_y - 1, 0xFF0000);
	my_mlx_pixel_put(data, hit_x, hit_y + 1, 0xFF0000);
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
