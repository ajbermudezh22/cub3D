/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:05:00 by albermud          #+#    #+#             */
/*   Updated: 2025/06/30 08:08:17 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_ray_step_sidedist(t_data *data, t_ray *ray)
{
	float	px_map;
	float	py_map;

	px_map = ray->px / data->map_s;
	py_map = ray->py / data->map_s;
	if (ray->dx < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (px_map - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0f - px_map) * ray->delta_dist_x;
	}
	if (ray->dy < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (py_map - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0f - py_map) * ray->delta_dist_y;
	}
}

void	init_ray(t_data *data, t_ray *ray, float ray_angle)
{
	ray->angle = ray_angle;
	while (ray->angle < 0)
		ray->angle += 2 * PI;
	while (ray->angle >= 2 * PI)
		ray->angle -= 2 * PI;
	ray->px = (float)data->player_x;
	ray->py = (float)data->player_y;
	ray->dx = cosf(ray->angle);
	ray->dy = sinf(ray->angle);
	ray->delta_dist_x = fabsf(1.0f / ray->dx);
	ray->delta_dist_y = fabsf(1.0f / ray->dy);
	ray->map_x = (int)(ray->px / data->map_s);
	ray->map_y = (int)(ray->py / data->map_s);
	init_ray_step_sidedist(data, ray);
}

void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= data->map_width
			|| ray->map_y < 0 || ray->map_y >= data->map_height
			|| data->map[ray->map_y * data->map_width + ray->map_x] == 1)
			hit = 1;
	}
}

float	cast_ray_3d(t_data *data, float ray_angle)
{
	t_ray	ray;
	float	distance;
	float	angle_diff;

	init_ray(data, &ray, ray_angle);
	perform_dda(data, &ray);
	if (ray.side == 0)
		ray.perp_wall_dist = (ray.map_x - ray.px / data->map_s
				+ (1 - ray.step_x) / 2) / ray.dx;
	else
		ray.perp_wall_dist = (ray.map_y - ray.py / data->map_s
				+ (1 - ray.step_y) / 2) / ray.dy;
	distance = ray.perp_wall_dist * data->map_s;
	angle_diff = ray.angle - data->player_angle;
	while (angle_diff > PI)
		angle_diff -= 2 * PI;
	while (angle_diff < -PI)
		angle_diff += 2 * PI;
	distance = distance * cosf(angle_diff);
	return (distance);
}

void	draw_hit_point(t_data *data, int hit_x, int hit_y)
{
	if (hit_x >= MAP_WIDTH)
		return ;
	my_mlx_pixel_put(data, hit_x, hit_y, 0xFF0000);
	my_mlx_pixel_put(data, hit_x - 1, hit_y, 0xFF0000);
	my_mlx_pixel_put(data, hit_x + 1, hit_y, 0xFF0000);
	my_mlx_pixel_put(data, hit_x, hit_y - 1, 0xFF0000);
	my_mlx_pixel_put(data, hit_x, hit_y + 1, 0xFF0000);
}
