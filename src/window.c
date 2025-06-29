/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:39 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 15:43:09 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_complete_view(t_data *data)
{
	clear_2d_view(data);
	clear_3d_view(data);
	draw_map_2d(data);
	draw_rays_2d(data);
	draw_player_2d(data);
	draw_separator(data);
	render_3d_view_textured(data, &data->texture);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	draw_separator(t_data *data)
{
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		my_mlx_pixel_put(data, MAP_WIDTH, y, 0xFFFFFF);
		my_mlx_pixel_put(data, MAP_WIDTH - 1, y, 0xFFFFFF);
	}
}
