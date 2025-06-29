/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:51:02 by albermud          #+#    #+#             */
/*   Updated: 2025/06/29 18:06:17 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_direction_line(t_data *data)
{
	int		line_length;
	float	end_x;
	float	end_y;
	int		thickness;

	if (data->player_x >= MAP_WIDTH)
		return ;
	line_length = 30;
	end_x = data->player_x + data->player_dx * line_length;
	end_y = data->player_y + data->player_dy * line_length;
	thickness = -3;
	while (++thickness <= 2)
		draw_thick_line(data, end_x, end_y, thickness);
}

void	draw_thick_line(t_data *data, float end_x, float end_y,
	int thickness)
{
	float	perpendicular_x;
	float	perpendicular_y;
	float	dx;
	float	dy;
	float	steps;
	float	x;
	float	y;
	int		step;

	perpendicular_x = -data->player_dy * thickness;
	perpendicular_y = data->player_dx * thickness;
	dx = end_x - data->player_x;
	dy = end_y - data->player_y;
	steps = fmax(fabs(dx), fabs(dy));
	if (steps <= 0)
		return ;
	dx /= steps;
	dy /= steps;
	x = data->player_x + perpendicular_x;
	y = data->player_y + perpendicular_y;
	step = -1;
	while (++step < (int)steps && x < MAP_WIDTH)
	{
		my_mlx_pixel_put(data, (int)x, (int)y, 0xFF0000);
		x += dx;
		y += dy;
	}
}

void	draw_rays_2d(t_data *data)
{
	int		i;
	int		num_rays;
	float	fov;
	float	start_angle;
	float	ray_angle;
	int		hit_x;
	int		hit_y;
	float	distance;
	int		color;

	num_rays = 60;
	fov = PI / 3;
	start_angle = data->player_angle - fov / 2;
	i = -1;
	while (++i < num_rays)
	{
		ray_angle = start_angle + (fov * i / num_rays);
		distance = cast_ray_2d(data, ray_angle, &hit_x, &hit_y);
		(void)distance;
		if (i == num_rays / 2)
			color = 0x00FF00;
		else
			color = 0x004400;
		draw_ray_line(data, hit_x, hit_y, color);
		draw_hit_point(data, hit_x, hit_y);
	}
}

void	draw_player_2d(t_data *data)
{
	draw_player_circle(data);
	draw_direction_line(data);
}
