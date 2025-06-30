/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:15:00 by albermud          #+#    #+#             */
/*   Updated: 2025/06/30 08:07:51 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	blend_colors(int color1, int color2, float alpha)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color1 >> 16) & 0xFF) * (1.0f - alpha)
			+ ((color2 >> 16) & 0xFF) * alpha);
	g = (int)(((color1 >> 8) & 0xFF) * (1.0f - alpha)
			+ ((color2 >> 8) & 0xFF) * alpha);
	b = (int)((color1 & 0xFF) * (1.0f - alpha)
			+ (color2 & 0xFF) * alpha);
	return ((r << 16) | (g << 8) | b);
}

static void	draw_aa_top_edge(t_data *data, t_wall *wall)
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

static void	draw_aa_bottom_edge(t_data *data, t_wall *wall)
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
	draw_aa_top_edge(data, wall);
	draw_aa_bottom_edge(data, wall);
}
