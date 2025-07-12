/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:39 by albbermu          #+#    #+#             */
/*   Updated: 2025/07/05 08:07:38 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_movement(int keycode, t_data *data,
				float *new_x, float *new_y)
{
	int	move_speed;

	move_speed = 5;
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
		*new_x += data->player_dy * move_speed;
		*new_y -= data->player_dx * move_speed;
	}
	if (keycode == 'd' || keycode == 'D')
	{
		*new_x -= data->player_dy * move_speed;
		*new_y += data->player_dx * move_speed;
	}
}

static void	handle_rotation(int keycode, float *new_angle)
{
	float	rotation_speed;

	rotation_speed = 0.1;
	if (keycode == KEY_LEFT)
		*new_angle -= rotation_speed;
	if (keycode == KEY_RIGHT)
		*new_angle += rotation_speed;
}

void	update_player_state(t_data *data, float new_x, float new_y,
	float new_angle)
{
	float	old_y;

	old_y = data->player_y;
	if (!is_wall(data, (int)new_x, (int)old_y))
	{
		data->player_x = new_x;
	}
	if (!is_wall(data, (int)data->player_x, (int)new_y))
	{
		data->player_y = new_y;
	}
	data->player_angle = new_angle;
	if (data->player_angle < 0)
		data->player_angle += 2 * PI;
	if (data->player_angle > 2 * PI)
		data->player_angle -= 2 * PI;
	data->player_dx = cos(data->player_angle);
	data->player_dy = sin(data->player_angle);
	render_complete_view(data);
}

int	key_hook(int keycode, t_data *data)
{
	float	new_x;
	float	new_y;
	float	new_angle;

	if (keycode == KEY_ESC)
	{
		mlx_loop_end(data->mlx);
		return (0);
	}
	new_x = data->player_x;
	new_y = data->player_y;
	new_angle = data->player_angle;
	handle_movement(keycode, data, &new_x, &new_y);
	handle_rotation(keycode, &new_angle);
	if (keycode == ' ')
	{
		data->view_mode = (data->view_mode + 1) % 3;
		resize_window(data);
	}
	if (new_x != data->player_x || new_y != data->player_y
		|| new_angle != data->player_angle)
	{
		update_player_state(data, new_x, new_y, new_angle);
	}
	return (0);
}

int	close_hook(t_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}
