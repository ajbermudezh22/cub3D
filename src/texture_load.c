/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:53:19 by albermud          #+#    #+#             */
/*   Updated: 2025/07/01 17:54:18 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
