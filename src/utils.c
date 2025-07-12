/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:00:00 by albermud          #+#    #+#             */
/*   Updated: 2025/07/12 12:00:00 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / data->map_s;
	map_y = y / data->map_s;
	if (map_x < 0 || map_x >= data->map_width || map_y < 0
		|| map_y >= data->map_height)
		return (1);
	return (data->map[map_y * data->map_width + map_x]);
}

void	draw_map_2d(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (data->map[y * data->map_width + x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x333333;
			draw_cell(data, x, y, color);
		}
	}
}

void	init_line_params(t_data *data, t_line_params *line_params,
	t_line_iter *p)
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

void	render_texture_ceiling(t_texture_wall_vars *vars, t_data *data,
	int screen_x, t_texture *tex)
{
	vars->y = 0;
	while (vars->y < vars->wall_start)
	{
		my_mlx_pixel_put(data, screen_x, vars->y,
			tex->ceiling_color);
		vars->y++;
	}
}

void	render_texture_floor(t_texture_wall_vars *vars, t_data *data,
	int screen_x, t_texture *tex)
{
	vars->y = vars->wall_end + 1;
	while (vars->y < HEIGHT)
	{
		my_mlx_pixel_put(data, screen_x, vars->y,
			tex->floor_color);
		vars->y++;
	}
}
