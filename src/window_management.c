/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 08:30:00 by albermud          #+#    #+#             */
/*   Updated: 2025/07/05 17:24:47 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	determine_new_dimensions(t_data *data, int *new_width,
	int *new_height)
{
	if (data->view_mode == 0)
	{
		*new_width = VIEW_WIDTH;
		*new_height = HEIGHT;
	}
	else if (data->view_mode == 1)
	{
		*new_width = MAP_WIDTH;
		*new_height = HEIGHT;
	}
	else
	{
		*new_width = WIDTH;
		*new_height = HEIGHT;
	}
	data->win_width = *new_width;
	data->win_height = *new_height;
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
	int	new_width;
	int	new_height;

	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	determine_new_dimensions(data, &new_width, &new_height);
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"Cub3D - 2D/3D View");
	if (!data->win)
	{
		printf("Error: Failed to create window\n");
		exit(1);
	}
	setup_window_hooks(data);
}
