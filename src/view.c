/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:28:00 by albermud          #+#    #+#             */
/*   Updated: 2025/07/05 08:11:34 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clear_3d_view(t_data *data)
{
	int	y;
	int	x;
	int	start_x;

	y = 0;
	if (data->view_mode == 2)
		start_x = MAP_WIDTH;
	else
		start_x = 0;
	while (y < data->win_height)
	{
		x = start_x;
		while (x < data->win_width)
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
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width && x < MAP_WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0x222222);
			x++;
		}
		y++;
	}
}
