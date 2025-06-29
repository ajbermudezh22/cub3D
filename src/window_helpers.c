/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:39 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 15:43:09 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_player_position(t_data *data, float new_x, float new_y)
{
	float	buffer;

	buffer = 8.0;
	if (!is_wall_with_buffer(data, new_x, data->player_y, buffer))
		data->player_x = new_x;
	if (!is_wall_with_buffer(data, data->player_x, new_y, buffer))
		data->player_y = new_y;
}

void	update_player_angle(t_data *data, float new_angle)
{
	data->player_angle = new_angle;
	if (data->player_angle < 0)
		data->player_angle += 2 * PI;
	if (data->player_angle > 2 * PI)
		data->player_angle -= 2 * PI;
	data->player_dx = cos(data->player_angle);
	data->player_dy = sin(data->player_angle);
}

void	handle_movement(int keycode, t_data *data, float *new_x, float *new_y)
{
	float	move_speed;

	move_speed = 3.0;
	if (keycode == 'w' || keycode == 'W')
	{
		*new_x += data->player_dx * move_speed;
		*new_y += data->player_dy * move_speed;
	}
	if (keycode == 's' || keycode == 'S')
	{
		*new_x -= data->player_dx * move_speed;
		*new_y -= data->player_dy * move_speed;
	}
	if (keycode == 'a' || keycode == 'A')
	{
		*new_x -= data->player_dy * move_speed;
		*new_y += data->player_dx * move_speed;
	}
	if (keycode == 'd' || keycode == 'D')
	{
		*new_x += data->player_dy * move_speed;
		*new_y -= data->player_dx * move_speed;
	}
}

void	handle_rotation(int keycode, float *new_angle)
{
	float	rotation_speed;

	rotation_speed = 0.1;
	if (keycode == KEY_LEFT)
		*new_angle -= rotation_speed;
	if (keycode == KEY_RIGHT)
		*new_angle += rotation_speed;
}
