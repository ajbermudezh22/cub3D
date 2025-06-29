/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:23 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 14:57:42 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_ray_line(t_data *data, int hit_x, int hit_y, int color)
{
	float	dx;
	float	dy;
	float	step_x;
	float	step_y;
	int		steps;
	int		i;
	float	x;
	float	y;

	dx = hit_x - data->player_x;
	dy = hit_y - data->player_y;
	if (abs((int)dx) > abs((int)dy))
		steps = abs((int)dx);
	else
		steps = abs((int)dy);
	step_x = dx / steps;
	step_y = dy / steps;
	x = data->player_x;
	y = data->player_y;
	i = -1;
	while (++i <= steps)
	{
		if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < HEIGHT)
			my_mlx_pixel_put(data, (int)x, (int)y, color);
		x += step_x;
		y += step_y;
	}
}

static void	draw_hit_point(t_data *data, int hit_x, int hit_y)
{
	int	size;
	int	i;
	int	j;

	size = 3;
	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			my_mlx_pixel_put(data, hit_x + i, hit_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

static void	draw_player_circle(t_data *data)
{
	int	radius;
	int	center_x;
	int	center_y;
	int	x;
	int	y;

	radius = 4;
	center_x = (int)data->player_x;
	center_y = (int)data->player_y;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				my_mlx_pixel_put(data, center_x + x, center_y + y, 0x0000FF);
			x++;
		}
		y++;
	}
}

static void	draw_direction_line(t_data *data)
{
	float	end_x;
	float	end_y;
	int		line_length;

	line_length = 20;
	end_x = data->player_x + cos(data->player_angle) * line_length;
	end_y = data->player_y + sin(data->player_angle) * line_length;
	draw_thick_line(data, end_x, end_y, 2);
}

void	draw_thick_line(t_data *data, float end_x, float end_y, int thickness)
{
	int	offset;

	offset = -thickness / 2;
	while (offset <= thickness / 2)
	{
		draw_ray_line(data, (int)end_x + offset, (int)end_y, 0x0000FF);
		draw_ray_line(data, (int)end_x, (int)end_y + offset, 0x0000FF);
		offset++;
	}
}

void	draw_rays_2d(t_data *data)
{
	float	ray_angle;
	int		hit_x;
	int		hit_y;
	int		ray_count;
	int		i;

	ray_count = 60;
	i = -1;
	while (++i < ray_count)
	{
		ray_angle = data->player_angle - (PI / 6) + (i * (PI / 3) / ray_count);
		cast_ray_2d(data, ray_angle, &hit_x, &hit_y);
		draw_ray_line(data, hit_x, hit_y, 0x00FF00);
		draw_hit_point(data, hit_x, hit_y);
	}
}

void	draw_player_2d(t_data *data)
{
	draw_player_circle(data);
	draw_direction_line(data);
}
