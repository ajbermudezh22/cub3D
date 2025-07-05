/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:54:54 by albermud          #+#    #+#             */
/*   Updated: 2025/07/05 08:06:11 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		exit(1);
	}
	data->win = NULL;
	data->img = NULL;
	resize_window(data);
}

void	init_textures(t_data *data)
{
	data->player_dx = cos(data->player_angle);
	data->player_dy = sin(data->player_angle);
	data->view_mode = 0;
	if (!load_textures(data))
	{
		printf("Error: Could not initialize textures\n");
		exit(1);
	}
	set_floor_ceiling_colors(&data->texture, &data->config);
}

void	render_complete_view(t_data *data)
{
	if (data->view_mode == 0)
	{
		clear_3d_view(data);
		render_3d_view_textured(data, &data->texture, 0);
	}
	else if (data->view_mode == 1)
	{
		clear_2d_view(data);
		draw_map_2d(data);
		draw_player_2d(data);
	}
	else
	{
		clear_2d_view(data);
		clear_3d_view(data);
		draw_map_2d(data);
		draw_player_2d(data);
		draw_separator(data);
		render_3d_view_textured(data, &data->texture, MAP_WIDTH);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	draw_separator(t_data *data)
{
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		my_mlx_pixel_put(data, MAP_WIDTH, y, 0xFFFFFF);
		my_mlx_pixel_put(data, MAP_WIDTH - 1, y, 0xFFFFFF);
	}
}

int	close_hook(t_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}
