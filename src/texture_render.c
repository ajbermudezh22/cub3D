/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:15:00 by albermud          #+#    #+#             */
/*   Updated: 2025/07/05 08:16:48 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_texture_wall_vars(t_texture_wall_vars *vars,
	t_ray_result ray_result, t_data *data, t_texture *tex)
{
	if (ray_result.distance <= 0)
		ray_result.distance = 1;
	vars->wall_height_f = (WALL_HEIGHT * data->map_s) / ray_result.distance;
	vars->wall_start = (HEIGHT / 2) - (vars->wall_height_f / 2);
	vars->wall_end = (HEIGHT / 2) + (vars->wall_height_f / 2);
	if (vars->wall_start < 0)
		vars->wall_start = 0;
	if (vars->wall_end >= HEIGHT)
		vars->wall_end = HEIGHT - 1;
	vars->tex_x = (int)(ray_result.wall_x * tex->tex_width);
	if (ray_result.side == 0 && ray_result.step_x > 0)
		vars->tex_x = tex->tex_width - vars->tex_x - 1;
	if (ray_result.side == 1 && ray_result.step_y < 0)
		vars->tex_x = tex->tex_width - vars->tex_x - 1;
}

void	render_texture_wall_pixels(t_texture_wall_vars *vars,
	t_wall_pixel_params *params)
{
	vars->y = vars->wall_start;
	while (vars->y <= vars->wall_end)
	{
		vars->tex_y = (int)(((float)(vars->y - vars->wall_start)
					/ (vars->wall_end - vars->wall_start))
				* params->tex->tex_height);
		vars->color = get_texture_pixel(params->tex,
				params->ray_result.wall_side, vars->tex_x, vars->tex_y);
		vars->shade_factor = 1.0f - (params->ray_result.distance
				/ (params->data->map_width * params->data->map_s * 0.5f));
		if (vars->shade_factor < 0.1f)
			vars->shade_factor = 0.1f;
		vars->r = ((vars->color >> 16) & 0xFF) * vars->shade_factor;
		vars->g = ((vars->color >> 8) & 0xFF) * vars->shade_factor;
		vars->b = (vars->color & 0xFF) * vars->shade_factor;
		my_mlx_pixel_put(params->data, params->screen_x, vars->y,
			(vars->r << 16) | (vars->g << 8) | vars->b);
		vars->y++;
	}
}

static void	draw_top_edge(t_data *data, t_wall *wall)
{
	float	alpha;
	int		blended;
	int		wall_base;

	if (wall->wall_start_f > 0 && wall->wall_start_f < HEIGHT)
	{
		alpha = wall->wall_start_f - (int)wall->wall_start_f;
		if (alpha > 0 && wall->wall_start > 0)
		{
			wall_base = (int)(180 * wall->shade_factor);
			blended = blend_colors(0x001144,
					wall_base << 16 | wall_base << 8 | wall_base, alpha);
			my_mlx_pixel_put(data, MAP_WIDTH + wall->x,
				wall->wall_start - 1, blended);
		}
	}
}

static void	draw_bottom_edge(t_data *data, t_wall *wall)
{
	float	alpha;
	int		blended;
	int		wall_base;

	if (wall->wall_end_f < HEIGHT - 1 && wall->wall_end_f > 0)
	{
		alpha = (int)(wall->wall_end_f + 1) - wall->wall_end_f;
		if (alpha > 0 && wall->wall_end < HEIGHT - 1)
		{
			wall_base = (int)(180 * wall->shade_factor);
			blended = blend_colors(
					wall_base << 16 | wall_base << 8 | wall_base,
					0x003300, alpha);
			my_mlx_pixel_put(data, MAP_WIDTH + wall->x,
				wall->wall_end + 1, blended);
		}
	}
}

void	draw_antialiased_edges(t_data *data, t_wall *wall)
{
	draw_top_edge(data, wall);
	draw_bottom_edge(data, wall);
}
