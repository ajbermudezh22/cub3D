/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:39 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 15:43:09 by albbermu         ###   ########.fr       */
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
		*new_x -= data->player_dy *  move_speed;
		*new_y += data->player_dx *  move_speed;
	}
	if (keycode == 'd' || keycode == 'D')
	{
		*new_x += data->player_dy * move_speed;
		*new_y -= data->player_dx * move_speed;
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

// int	key_hook(int keycode, t_data *data)
// {
// 	float	new_x;
// 	float	new_y;
// 	float	new_angle;

// 	new_x = data->player_x;
// 	new_y = data->player_y;
// 	new_angle = data->player_angle;
// 	handle_movement(keycode, data, &new_x, &new_y);
// 	handle_rotation(keycode, &new_angle);
// 	if (keycode == ' ')
// 		data->view_mode = (data->view_mode + 1) % 3;
// 	if (!is_wall((int)new_x, (int)new_y) &&
// 		new_x >= 10 && new_x < MAP_WIDTH - 10 &&
// 		new_y >= 10 && new_y < HEIGHT - 10)
// 	{
// 		data->player_x = new_x;
// 		data->player_y = new_y;
// 	}
// 	data->player_angle = new_angle;
// 	if (data->player_angle < 0)
//         data->player_angle += 2 * PI;
// 	if (data->player_angle > 2 * PI)
//         data->player_angle -= 2 * PI;
// 	data->player_dx = cos(data->player_angle);
// 	data->player_dy = sin(data->player_angle);
// 	render_complete_view(data);
// 	return (0);
// }

// ...existing code...
int	key_hook(int keycode, t_data *data)
{
    float	new_x;
    float	new_y;
    float	new_angle;
    // float	old_x;
    float	old_y;

    new_x = data->player_x;
    new_y = data->player_y;
    // old_x = data->player_x;
    old_y = data->player_y;
    new_angle = data->player_angle;
    handle_movement(keycode, data, &new_x, &new_y);
    handle_rotation(keycode, &new_angle);
    if (keycode == ' ')
        data->view_mode = (data->view_mode + 1) % 3;
    
    // Implement wall sliding for smoother, more robust collision.
    // This checks X and Y movement independently.
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
    return (0);
}