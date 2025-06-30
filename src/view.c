/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:28:00 by albermud          #+#    #+#             */
/*   Updated: 2025/06/30 08:08:45 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clear_3d_view(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = MAP_WIDTH;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	clear_2d_view(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0x222222);
			x++;
		}
		y++;
	}
}
