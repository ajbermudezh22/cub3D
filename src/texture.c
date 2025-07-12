/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:34 by albbermu          #+#    #+#             */
/*   Updated: 2025/07/01 18:35:10 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	determine_texture_wall_side(t_ray_result *result)
{
	if (result->side == 0)
	{
		if (result->step_x > 0)
			result->wall_side = 2;
		else
			result->wall_side = 3;
	}
	else
	{
		if (result->step_y > 0)
			result->wall_side = 0;
		else
			result->wall_side = 1;
	}
}

t_ray_result	cast_ray_with_texture_info(t_data *data, float ray_angle)
{
	t_ray_result			result;
	t_raycast				vars;

	normalize_ray_angle(&ray_angle);
	init_texture_raycast(data, &vars, ray_angle);
	setup_texture_step_dist(&vars, &result, data);
	execute_texture_dda(&vars, &result, data);
	set_wall_distance(&vars, &result, data);
	determine_texture_wall_side(&result);
	return (result);
}

void	draw_textured_wall_slice(t_data *data, int screen_x,
	t_ray_result ray_result, t_texture *tex)
{
	t_texture_wall_vars	vars;
	t_wall_pixel_params	params;

	params.data = data;
	params.screen_x = screen_x;
	params.ray_result = ray_result;
	params.tex = tex;
	init_texture_wall_vars(&vars, ray_result, data, tex);
	render_texture_ceiling(&vars, data, screen_x, tex);
	render_texture_wall_pixels(&vars, &params);
	render_texture_floor(&vars, data, screen_x, tex);
}

static int	load_single_texture(void *mlx, t_texture_details *details,
	int *w, int *h)
{
	int	bpp;
	int	len;
	int	end;

	*details->texture = mlx_xpm_file_to_image(mlx, details->path, w, h);
	if (!*details->texture)
	{
		printf("Error: Failed to load texture: %s\n", details->path);
		return (0);
	}
	*details->addr = (int *)mlx_get_data_addr(*details->texture, &bpp, &len,
			&end);
	printf("✓ %s texture loaded: %s\n", details->name, details->path);
	return (1);
}

int	load_textures(t_data *data)
{
	t_texture_details	details[4];

	data->texture.north_texture = NULL;
	data->texture.south_texture = NULL;
	data->texture.west_texture = NULL;
	data->texture.east_texture = NULL;
	details[0] = (t_texture_details){"North", data->config.north_texture_path,
		&data->texture.north_texture, &data->texture.north_addr};
	details[1] = (t_texture_details){"South", data->config.south_texture_path,
		&data->texture.south_texture, &data->texture.south_addr};
	details[2] = (t_texture_details){"West", data->config.west_texture_path,
		&data->texture.west_texture, &data->texture.west_addr};
	details[3] = (t_texture_details){"East", data->config.east_texture_path,
		&data->texture.east_texture, &data->texture.east_addr};
	if (!load_single_texture(data->mlx, &details[0], &data->texture.tex_width,
			&data->texture.tex_height)
		|| !load_single_texture(data->mlx, &details[1],
			&data->texture.tex_width, &data->texture.tex_height)
		|| !load_single_texture(data->mlx, &details[2],
			&data->texture.tex_width, &data->texture.tex_height)
		|| !load_single_texture(data->mlx, &details[3],
			&data->texture.tex_width, &data->texture.tex_height))
		return (0);
	return (1);
}
