/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:30:44 by albermud          #+#    #+#             */
/*   Updated: 2025/07/05 08:20:15 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static void	init_thick_line_params(t_data *data, t_line_iter *p,
	t_line_params *line_params)
{
	float	perpendicular_x;
	float	perpendicular_y;

	perpendicular_x = -data->player_dy * line_params->thickness;
	perpendicular_y = data->player_dx * line_params->thickness;
	p->dx = line_params->end_x - data->player_x;
	p->dy = line_params->end_y - data->player_y;
	p->steps = fmax(fabs(p->dx), fabs(p->dy));
	if (p->steps > 0)
	{
		p->dx /= p->steps;
		p->dy /= p->steps;
	}
	p->x = data->player_x + perpendicular_x;
	p->y = data->player_y + perpendicular_y;
}

void	draw_thick_line(t_data *data, t_line_params *line_params)
{
	t_line_iter	p;
	int			step;

	init_thick_line_params(data, &p, line_params);
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
