/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:51:02 by albermud          #+#    #+#             */
/*   Updated: 2025/06/29 18:31:28 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_and_draw_ray(t_data *data, t_ray_params *p, int i)
{
	p->ray_angle = p->start_angle + (p->fov * i / p->num_rays);
	p->distance = cast_ray_2d(data, p->ray_angle, &p->hit_x, &p->hit_y);
	(void)p->distance;
	if (i == p->num_rays / 2)
		p->color = 0x00FF00;
	else
		p->color = 0x004400;
	draw_ray_line(data, p->hit_x, p->hit_y, p->color);
	draw_hit_point(data, p->hit_x, p->hit_y);
}

void	draw_rays_2d(t_data *data)
{
	t_ray_params	p;
	int				i;

	p.num_rays = 60;
	p.fov = PI / 3;
	p.start_angle = data->player_angle - p.fov / 2;
	i = -1;
	while (++i < p.num_rays)
		cast_and_draw_ray(data, &p, i);
}

void	draw_player_2d(t_data *data)
{
	draw_player_circle(data);
	draw_direction_line(data);
}
