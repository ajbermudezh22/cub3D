/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:51:59 by albermud          #+#    #+#             */
/*   Updated: 2025/07/05 08:06:12 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(void *mlx, t_texture *tex)
{
	if (tex->north_texture)
		mlx_destroy_image(mlx, tex->north_texture);
	if (tex->south_texture)
		mlx_destroy_image(mlx, tex->south_texture);
	if (tex->west_texture)
		mlx_destroy_image(mlx, tex->west_texture);
	if (tex->east_texture)
		mlx_destroy_image(mlx, tex->east_texture);
}

int	get_texture_pixel(t_texture *tex, int wall_side, int tex_x, int tex_y)
{
	int	*texture_addr;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->tex_width)
		tex_x = tex->tex_width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->tex_height)
		tex_y = tex->tex_height - 1;
	if (wall_side == 0)
		texture_addr = tex->north_addr;
	else if (wall_side == 1)
		texture_addr = tex->south_addr;
	else if (wall_side == 2)
		texture_addr = tex->west_addr;
	else if (wall_side == 3)
		texture_addr = tex->east_addr;
	else
		texture_addr = tex->north_addr;
	if (!texture_addr)
		return (0xFF0000);
	return (texture_addr[tex_y * tex->tex_width + tex_x]);
}

void	render_3d_view_textured(t_data *data, t_texture *tex, int x_offset)
{
	float			fov_rad;
	int				x;
	float			camera_x;
	float			ray_angle;
	t_ray_result	ray_result;

	fov_rad = FOV * DR;
	x = 0;
	while (x < VIEW_WIDTH)
	{
		camera_x = 2.0f * x / (float)VIEW_WIDTH - 1.0f;
		ray_angle = data->player_angle + atanf(camera_x * tanf(fov_rad / 2.0f));
		ray_result = cast_ray_with_texture_info(data, ray_angle);
		draw_textured_wall_slice(data, x + x_offset, ray_result, tex);
		x++;
	}
}

void	set_floor_ceiling_colors(t_texture *tex, t_config *config)
{
	tex->floor_color = (config->floor_r << 16)
		| (config->floor_g << 8) | config->floor_b;
	tex->ceiling_color = (config->ceiling_r << 16)
		| (config->ceiling_g << 8) | config->ceiling_b;
}

int	blend_colors(int color1, int color2, float alpha)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color1 >> 16) & 0xFF) * (1.0f - alpha)
			+ ((color2 >> 16) & 0xFF) * alpha);
	g = (int)(((color1 >> 8) & 0xFF) * (1.0f - alpha)
			+ ((color2 >> 8) & 0xFF) * alpha);
	b = (int)((color1 & 0xFF) * (1.0f - alpha)
			+ (color2 & 0xFF) * alpha);
	return ((r << 16) | (g << 8) | b);
}
