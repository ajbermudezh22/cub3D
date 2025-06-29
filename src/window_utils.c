/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:54:54 by albermud          #+#    #+#             */
/*   Updated: 2025/06/29 18:58:40 by albermud         ###   ########.fr       */
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
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D - 2D/3D View");
	if (!data->win)
	{
		printf("Error: Failed to create window\n");
		exit(1);
	}
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

void	init_textures(t_data *data)
{
	data->player_dx = cos(data->player_angle);
	data->player_dy = sin(data->player_angle);
	data->view_mode = 1;
	if (!load_textures(data->mlx, &data->texture,
			data->config.north_texture_path,
			data->config.south_texture_path,
			data->config.west_texture_path,
			data->config.east_texture_path))
	{
		printf("Error: Could not initialize textures\n");
		exit(1);
	}
	set_floor_ceiling_colors(&data->texture,
		data->config.floor_r, data->config.floor_g, data->config.floor_b,
		data->config.ceiling_r, data->config.ceiling_g, data->config.ceiling_b);
}

void	render_complete_view(t_data *data)
{
	clear_2d_view(data);
	clear_3d_view(data);
	draw_map_2d(data);
	draw_rays_2d(data);
	draw_player_2d(data);
	draw_separator(data);
	render_3d_view_textured(data, &data->texture);
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
	cleanup_program(data);
	exit(0);
	return (0);
}
