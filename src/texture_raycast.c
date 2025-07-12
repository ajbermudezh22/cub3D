/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:10:00 by albermud          #+#    #+#             */
/*   Updated: 2025/07/01 18:41:39 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	normalize_ray_angle(float *ray_angle)
{
	while (*ray_angle < 0)
		*ray_angle += 2 * M_PI;
	while (*ray_angle >= 2 * M_PI)
		*ray_angle -= 2 * M_PI;
}

void	init_texture_raycast(t_data *data, t_raycast *vars,
	float ray_angle)
{
	vars->px = data->player_x;
	vars->py = data->player_y;
	vars->dx = cos(ray_angle);
	vars->dy = sin(ray_angle);
	vars->delta_dist_x = fabs(1.0f / vars->dx);
	vars->delta_dist_y = fabs(1.0f / vars->dy);
	vars->map_x = (int)(vars->px / data->map_s);
	vars->map_y = (int)(vars->py / data->map_s);
	vars->hit = 0;
}

void	setup_texture_step_dist(t_raycast *vars,
	t_ray_result *result, t_data *data)
{
	if (vars->dx < 0)
	{
		result->step_x = -1;
		vars->side_dist_x = (vars->px / data->map_s - vars->map_x)
			* vars->delta_dist_x;
	}
	else
	{
		result->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0f - vars->px / data->map_s)
			* vars->delta_dist_x;
	}
	if (vars->dy < 0)
	{
		result->step_y = -1;
		vars->side_dist_y = (vars->py / data->map_s - vars->map_y)
			* vars->delta_dist_y;
	}
	else
	{
		result->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0f - vars->py / data->map_s)
			* vars->delta_dist_y;
	}
}

void	execute_texture_dda(t_raycast *vars,
	t_ray_result *result, t_data *data)
{
	while (vars->hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += result->step_x;
			result->side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += result->step_y;
			result->side = 1;
		}
		if (vars->map_x < 0 || vars->map_x >= data->map_width
			|| vars->map_y < 0 || vars->map_y >= data->map_height
			|| data->map[vars->map_y * data->map_width + vars->map_x] == 1)
			vars->hit = 1;
	}
}

void	set_wall_distance(t_raycast *vars, t_ray_result *result, t_data *data)
{
	float	ray_angle;
	float	angle_diff;

	vars->perp_wall_dist = (vars->map_x - vars->px / data->map_s
			+ (1 - result->step_x) / 2) / vars->dx;
	result->wall_x = vars->py / data->map_s + vars->perp_wall_dist
		* vars->dy;
	if (result->side != 0)
	{
		vars->perp_wall_dist = (vars->map_y - vars->py / data->map_s
				+ (1 - result->step_y) / 2) / vars->dy;
		result->wall_x = vars->px / data->map_s + vars->perp_wall_dist
			* vars->dx;
	}
	result->wall_x -= floor(result->wall_x);
	result->distance = vars->perp_wall_dist * data->map_s;
	ray_angle = atan2(vars->dy, vars->dx);
	angle_diff = ray_angle - data->player_angle;
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	result->distance *= cos(angle_diff);
}
