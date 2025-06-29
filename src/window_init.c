/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:39 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 15:43:09 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_mlx_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D - 2D/3D View");
	if (!data->win)
	{
		printf("Error: Failed to create window\n");
		exit(1);
	}
}

static void	init_mlx_image(t_data *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		printf("Error: Failed to create image\n");
		exit(1);
	}
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_len, &data->endian);
	if (!data->addr)
	{
		printf("Error: Failed to get image data address\n");
		exit(1);
	}
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		exit(1);
	}
	init_mlx_window(data);
	init_mlx_image(data);
}

static void	load_texture_files(t_data *data)
{
	if (!load_textures(data->mlx, &data->texture,
			data->config.north_texture_path,
			data->config.south_texture_path,
			data->config.west_texture_path,
			data->config.east_texture_path))
	{
		printf("Error: Could not initialize textures\n");
		exit(1);
	}
}

void	init_textures(t_data *data)
{
	data->player_dx = cos(data->player_angle);
	data->player_dy = sin(data->player_angle);
	data->view_mode = 1;
	load_texture_files(data);
	set_floor_ceiling_colors(&data->texture,
		data->config.floor_r, data->config.floor_g, data->config.floor_b,
		data->config.ceiling_r, data->config.ceiling_g, data->config.ceiling_b);
}
