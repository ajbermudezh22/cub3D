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

static void	setup_window_hooks(t_data *data)
{
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!data->img)
	{
		printf("Error: Failed to create image\n");
		exit(1);
	}
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_len, &data->endian);
	mlx_hook(data->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win, 17, 0L, close_hook, data);
	render_complete_view(data);
}

void	resize_window(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->view_mode == 0)
		data->win_width = VIEW_WIDTH;
	else if (data->view_mode == 1)
		data->win_width = MAP_WIDTH;
	else
		data->win_width = WIDTH;
	data->win_height = HEIGHT;
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"Cub3D - 2D/3D View");
	if (!data->win)
	{
		printf("Error: Failed to create window\n");
		exit(1);
	}
	setup_window_hooks(data);
}
