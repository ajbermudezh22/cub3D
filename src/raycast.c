/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:23 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 14:57:42 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_wall_hit(t_data *data, float current_x, float current_y);
static float	calculate_distance(t_data *data, float current_x, float current_y);
static void	draw_ray_line(t_data *data, int hit_x, int hit_y, int color);
static void	draw_hit_point(t_data *data, int hit_x, int hit_y);
static void	draw_player_circle(t_data *data);
static void	draw_direction_line(t_data *data);
static void	draw_thick_line(t_data *data, float end_x, float end_y, int thickness);

float	cast_ray_2d(t_data *data, float ray_angle, int *hit_x, int *hit_y)
{
	float	dx;
	float	dy;
	float	current_x;
	float	current_y;
	float	step_size;

	dx = cos(ray_angle);
	dy = sin(ray_angle);
	current_x = data->player_x;
	current_y = data->player_y;
	step_size = 0.5;
	while (1)
	{
		current_x += dx * step_size;
		current_y += dy * step_size;
		if (current_x < 0 || current_x >= MAP_WIDTH ||
			current_y < 0 || current_y >= HEIGHT)
			break ;
		if (check_wall_hit(data, current_x, current_y))
		{
			float distance = calculate_distance(data, current_x, current_y);
			float angle_diff = ray_angle - data->player_angle;
			return (distance * cos(angle_diff));
		}
	}
	*hit_x = (int)current_x;
	*hit_y = (int)current_y;
	float distance = calculate_distance(data, current_x, current_y);
	float angle_diff = ray_angle - data->player_angle;
	return (distance * cos(angle_diff));
}

static int	check_wall_hit(t_data *data, float current_x, float current_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)current_x / data->map.tile_size;
	map_y = (int)current_y / data->map.tile_size;
	if (map_x >= 0 && map_x < data->map.width
		&& map_y >= 0 && map_y < data->map.height)
	{
		if (data->map.grid[map_y * data->map.width + map_x] == 1)
			return (1);
	}
	return (0);
}

static float	calculate_distance(t_data *data, float current_x, float current_y)
{
	return (sqrt(pow(current_x - data->player_x, 2) +
		pow(current_y - data->player_y, 2)));
}

static void	draw_ray_line(t_data *data, int hit_x, int hit_y, int color)
{
	float	dx;
	float	dy;
	float	steps;
	float	x;
	float	y;
	int		step;

	if (hit_x >= MAP_WIDTH)
		return ;
	dx = hit_x - data->player_x;
	dy = hit_y - data->player_y;
	steps = fmax(fabs(dx), fabs(dy));
	if (steps <= 0)
		return ;
	dx /= steps;
	dy /= steps;
	x = data->player_x;
	y = data->player_y;
	step = -1;
	while (++step < (int)steps && x < MAP_WIDTH)
	{
		my_mlx_pixel_put(data, (int)x, (int)y, color);
		x += dx;
		y += dy;
	}
}

static void	draw_hit_point(t_data *data, int hit_x, int hit_y)
{
	if (hit_x >= MAP_WIDTH)
		return ;
	my_mlx_pixel_put(data, hit_x, hit_y, 0xFF0000);
	my_mlx_pixel_put(data, hit_x - 1, hit_y, 0xFF0000);
	my_mlx_pixel_put(data, hit_x + 1, hit_y, 0xFF0000);
	my_mlx_pixel_put(data, hit_x, hit_y - 1, 0xFF0000);
	my_mlx_pixel_put(data, hit_x, hit_y + 1, 0xFF0000);
}

static void	draw_player_circle(t_data *data)
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

static void	draw_direction_line(t_data *data)
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

static void	draw_thick_line(t_data *data, float end_x, float end_y, int thickness)
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
