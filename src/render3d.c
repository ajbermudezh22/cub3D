/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:27 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/30 08:07:45 by albermud         ###   ########.fr       */
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
