/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:57:51 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/26 15:59:06 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        char *dst = (char *)data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

int blend_colors(int color1, int color2, float alpha)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;
	
	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;
	
	int r = (int)(r1 * (1.0f - alpha) + r2 * alpha);
	int g = (int)(g1 * (1.0f - alpha) + g2 * alpha);
	int b = (int)(b1 * (1.0f - alpha) + b2 * alpha);
	
	return (r << 16) | (g << 8) | b;
}
