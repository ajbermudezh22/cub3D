/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:51:02 by albermud          #+#    #+#             */
/*   Updated: 2025/06/30 18:16:47 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_and_draw_ray(t_data *data, t_ray_params *p, int i)
{
	p->ray_angle = p->start_angle + (p->fov * i / p->num_rays);
	p->distance = cast_ray_2d(data, p->ray_angle, &p->hit_x, &p->hit_y);
	(void)p->distance;
	if (i == p->num_rays / 2)
		p->color = 0xFF00FF;
	else
		p->color = 0xFFFF00;
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

void	draw_direction_line(t_data *data)
{
	int					line_length;
	t_line_params		line_params;
	int					thickness;

	if (data->player_x >= MAP_WIDTH)
		return ;
	line_length = 30;
	line_params.end_x = data->player_x + data->player_dx * line_length;
	line_params.end_y = data->player_y + data->player_dy * line_length;
	thickness = -3;
	while (++thickness <= 2)
	{
		line_params.thickness = thickness;
		draw_thick_line(data, &line_params);
	}
}

void	draw_thick_line(t_data *data, t_line_params *line_params)
{
	t_line_iter	p;
	int			step;

	init_line_params(data, line_params, &p);
	if (p.steps <= 0)
		return ;
	step = -1;
	while (++step < (int)p.steps && p.x < MAP_WIDTH)
	{
		my_mlx_pixel_put(data, (int)p.x, (int)p.y, 0xFF0000);
		p.x += p.dx;
		p.y += p.dy;
	}
}
