/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:34 by albbermu          #+#    #+#             */
/*   Updated: 2025/07/01 17:55:10 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_ray_result	cast_ray_with_texture_info(t_data *data, float ray_angle)
{
	t_ray_result	result;
	float			px;
	float			py;
	float			dx;
	float			dy;
	float			delta_dist_x;
	float			delta_dist_y;
	int				map_x;
	int				map_y;
	float			side_dist_x;
	float			side_dist_y;
	int				hit;
	float			perp_wall_dist;

	while (ray_angle < 0)
		ray_angle += 2 * M_PI;
	while (ray_angle >= 2 * M_PI)
		ray_angle -= 2 * M_PI;
	px = data->player_x;
	py = data->player_y;
	dx = cos(ray_angle);
	dy = sin(ray_angle);
	delta_dist_x = fabs(1.0f / dx);
	delta_dist_y = fabs(1.0f / dy);
	map_x = (int)(px / data->map_s);
	map_y = (int)(py / data->map_s);
	if (dx < 0)
	{
		result.step_x = -1;
		side_dist_x = (px / data->map_s - map_x) * delta_dist_x;
	}
	else
	{
		result.step_x = 1;
		side_dist_x = (map_x + 1.0f - px / data->map_s) * delta_dist_x;
	}
	if (dy < 0)
	{
		result.step_y = -1;
		side_dist_y = (py / data->map_s - map_y) * delta_dist_y;
	}
	else
	{
		result.step_y = 1;
		side_dist_y = (map_y + 1.0f - py / data->map_s) * delta_dist_y;
	}
	hit = 0;
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += result.step_x;
			result.side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += result.step_y;
			result.side = 1;
		}
		if (map_x < 0 || map_x >= data->map_width || map_y < 0
			|| map_y >= data->map_height
			|| data->map[map_y * data->map_width + map_x] == 1)
			hit = 1;
	}
	if (result.side == 0)
	{
		perp_wall_dist = (map_x - px / data->map_s + (1 - result.step_x) / 2) / dx;
		result.wall_x = py / data->map_s + perp_wall_dist * dy;
	}
	else
	{
		perp_wall_dist = (map_y - py / data->map_s + (1 - result.step_y) / 2) / dy;
		result.wall_x = px / data->map_s + perp_wall_dist * dx;
	}
	result.wall_x -= floor(result.wall_x);
	if (result.side == 0)
	{
		if (result.step_x > 0)
			result.wall_side = 2;
		else
			result.wall_side = 3;
	}
	else
	{
		if (result.step_y > 0)
			result.wall_side = 0;
		else
			result.wall_side = 1;
	}
	result.distance = perp_wall_dist * data->map_s;
	return (result);
}

void	draw_textured_wall_slice(t_data *data, int screen_x,
	t_ray_result ray_result, t_texture *tex)
{
	float	wall_height_f;
	int		wall_start;
	int		wall_end;
	int		tex_x;
	int		y;
	int		tex_y;
	int		color;
	float	shade_factor;
	int		r;
	int		g;
	int		b;

	if (ray_result.distance <= 0)
		ray_result.distance = 1;
	wall_height_f = (WALL_HEIGHT * data->map_s) / ray_result.distance;
	wall_start = (HEIGHT / 2) - (wall_height_f / 2);
	wall_end = (HEIGHT / 2) + (wall_height_f / 2);
	if (wall_start < 0)
		wall_start = 0;
	if (wall_end >= HEIGHT)
		wall_end = HEIGHT - 1;
	tex_x = (int)(ray_result.wall_x * tex->tex_width);
	if (ray_result.side == 0 && ray_result.step_x > 0)
		tex_x = tex->tex_width - tex_x - 1;
	if (ray_result.side == 1 && ray_result.step_y < 0)
		tex_x = tex->tex_width - tex_x - 1;
	y = 0;
	while (y < wall_start)
	{
		my_mlx_pixel_put(data, MAP_WIDTH + screen_x, y, tex->ceiling_color);
		y++;
	}
	y = wall_start;
	while (y <= wall_end)
	{
		tex_y = (int)(((float)(y - wall_start) / (wall_end - wall_start))
				* tex->tex_height);
		color = get_texture_pixel(tex, ray_result.wall_side, tex_x, tex_y);
		shade_factor = 1.0f - (ray_result.distance
				/ (data->map_width * data->map_s * 0.5f));
		if (shade_factor < 0.1f)
			shade_factor = 0.1f;
		r = ((color >> 16) & 0xFF) * shade_factor;
		g = ((color >> 8) & 0xFF) * shade_factor;
		b = (color & 0xFF) * shade_factor;
		my_mlx_pixel_put(data, MAP_WIDTH + screen_x, y, (r << 16) | (g << 8) | b);
		y++;
	}
	y = wall_end + 1;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data, MAP_WIDTH + screen_x, y, tex->floor_color);
		y++;
	}
}
