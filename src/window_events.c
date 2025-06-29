/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:39 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 15:43:09 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_hook(int keycode, t_data *data)
{
	float	new_x;
	float	new_y;
	float	new_angle;

	if (keycode == KEY_ESC)
		close_window(data);
	new_x = data->player_x;
	new_y = data->player_y;
	new_angle = data->player_angle;
	handle_movement(keycode, data, &new_x, &new_y);
	handle_rotation(keycode, &new_angle);
	if (keycode == ' ')
		data->view_mode = (data->view_mode + 1) % 3;
	update_player_position(data, new_x, new_y);
	update_player_angle(data, new_angle);
	render_complete_view(data);
	return (0);
}

int	close_window(t_data *data)
{
	free_textures(data->mlx, &data->texture);
	free_config(&data->config);
	if (data->map.grid)
		free(data->map.grid);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}
