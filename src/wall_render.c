/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:10:00 by albermud          #+#    #+#             */
/*   Updated: 2025/07/06 08:37:24 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_wall(t_data *data, t_wall *wall, int x, float distance)
{
	wall->x = x;
	wall->distance = distance;
	if (wall->distance <= 0)
		wall->distance = 1;
	wall->wall_height_f = (WALL_HEIGHT * data->map_s) / wall->distance;
	wall->wall_start_f = (HEIGHT / 2.0f) - (wall->wall_height_f / 2.0f);
	wall->wall_end_f = (HEIGHT / 2.0f) + (wall->wall_height_f / 2.0f);
	wall->wall_start = (int)wall->wall_start_f;
	wall->wall_end = (int)wall->wall_end_f;
	if (wall->wall_start < 0)
		wall->wall_start = 0;
	if (wall->wall_end >= HEIGHT)
		wall->wall_end = HEIGHT - 1;
	wall->shade_factor = 1.0f - (wall->distance / 400.0f);
	if (wall->shade_factor < 0.1f)
		wall->shade_factor = 0.1f;
	if (wall->shade_factor > 1.0f)
		wall->shade_factor = 1.0f;
}

void	draw_ceiling(t_data *data, t_wall *wall)
{
	int		y;

	y = 0;
	while (y < wall->wall_start)
	{
		my_mlx_pixel_put(data, MAP_WIDTH + wall->x, y,
			data->texture.ceiling_color);
		y++;
	}
}

void	draw_floor(t_data *data, t_wall *wall)
{
	int		y;

	y = wall->wall_end + 1;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(data, MAP_WIDTH + wall->x, y,
			data->texture.floor_color);
		y++;
	}
}

static int	calculate_wall_color(t_wall *wall, float wall_pos, int x)
{
	float	tex_var;
	int		final_shade;

	tex_var = 1.0f;
	if (fmodf(wall_pos * 8.0f, 1.0f) < 0.1f
		|| fmodf(wall_pos * 8.0f, 1.0f) > 0.9f)
		tex_var *= 0.85f;
	tex_var *= 1.0f + 0.1f * sinf(x * 0.3f);
	tex_var *= 1.0f + 0.05f * sinf(x * 0.7f + wall_pos * 15.0f);
	final_shade = (int)((180 * wall->shade_factor) * tex_var);
	if (final_shade < 0)
		final_shade = 0;
	if (final_shade > 255)
		final_shade = 255;
	return ((final_shade << 16) | ((int)(final_shade * 0.95f) << 8)
		| (int)(final_shade * 0.9f));
}

void	draw_textured_wall(t_data *data, t_wall *wall)
{
	int		y;
	float	wall_pos;
	int		color;

	y = wall->wall_start;
	while (y <= wall->wall_end && y < HEIGHT)
	{
		wall_pos = (float)(y - wall->wall_start_f) / wall->wall_height_f;
		color = calculate_wall_color(wall, wall_pos, wall->x);
		my_mlx_pixel_put(data, MAP_WIDTH + wall->x, y, color);
		y++;
	}
}
