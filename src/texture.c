/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:34 by albbermu          #+#    #+#             */
/*   Updated: 2025/07/01 18:35:10 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	determine_texture_wall_side(t_ray_result *result)
{
	if (result->side == 0)
	{
		if (result->step_x > 0)
			result->wall_side = 2;
		else
			result->wall_side = 3;
	}
	else
	{
		if (result->step_y > 0)
			result->wall_side = 0;
		else
			result->wall_side = 1;
	}
}

t_ray_result	cast_ray_with_texture_info(t_data *data, float ray_angle)
{
	t_ray_result			result;
	t_raycast				vars;

	normalize_ray_angle(&ray_angle);
	init_texture_raycast(data, &vars, ray_angle);
	setup_texture_step_dist(&vars, &result, data);
	execute_texture_dda(&vars, &result, data);
	set_wall_distance(&vars, &result, data);
	determine_texture_wall_side(&result);
	return (result);
}

void	draw_textured_wall_slice(t_data *data, int screen_x,
	t_ray_result ray_result, t_texture *tex)
{
	t_texture_wall_vars	vars;
	t_wall_pixel_params	params;

	params.data = data;
	params.screen_x = screen_x;
	params.ray_result = ray_result;
	params.tex = tex;
	init_texture_wall_vars(&vars, ray_result, data, tex);
	render_texture_ceiling(&vars, data, screen_x, tex);
	render_texture_wall_pixels(&vars, &params);
	render_texture_floor(&vars, data, screen_x, tex);
}
