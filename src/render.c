/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:00:00 by albermud          #+#    #+#             */
/*   Updated: 2025/07/12 12:00:00 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_wall_slice(t_data *data, int x, float distance, int wall_color)
{
	t_wall	wall;

	(void)wall_color;
	init_wall(data, &wall, x, distance);
	draw_ceiling(data, &wall);
	draw_textured_wall(data, &wall);
	draw_antialiased_edges(data, &wall);
	draw_floor(data, &wall);
}

void	render_3d_view(t_data *data)
{
	float		fov_rad;
	int			x;
	float		camera_x;
	float		ray_angle;
	float		distance;

	fov_rad = FOV * DR;
	x = 0;
	while (x < VIEW_WIDTH)
	{
		camera_x = 2.0f * x / (float)VIEW_WIDTH - 1.0f;
		ray_angle = data->player_angle + atanf(camera_x * tanf(fov_rad / 2.0f));
		distance = cast_ray_3d(data, ray_angle);
		draw_wall_slice(data, x, distance, 0xFFFFFF);
		x++;
	}
}

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
