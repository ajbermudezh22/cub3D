/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 07:30:10 by albermud          #+#    #+#             */
/*   Updated: 2025/06/30 06:55:45 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_config(t_config *config)
{
	config->north_texture_path = NULL;
	config->south_texture_path = NULL;
	config->west_texture_path = NULL;
	config->east_texture_path = NULL;
	config->floor_r = -1;
	config->floor_g = -1;
	config->floor_b = -1;
	config->ceiling_r = -1;
	config->ceiling_g = -1;
	config->ceiling_b = -1;
	config->map_grid = NULL;
	config->map_width = 0;
	config->map_height = 0;
	config->player_x = -1;
	config->player_y = -1;
	config->player_dir = '\0';
}

void	free_config(t_config *config)
{
	int	i;

	if (config->north_texture_path)
		free(config->north_texture_path);
	if (config->south_texture_path)
		free(config->south_texture_path);
	if (config->west_texture_path)
		free(config->west_texture_path);
	if (config->east_texture_path)
		free(config->east_texture_path);
	if (config->map_grid)
	{
		i = 0;
		while (i < config->map_height)
		{
			if (config->map_grid[i])
				free(config->map_grid[i]);
			i++;
		}
		free(config->map_grid);
	}
}

int	check_config_complete(t_config *config)
{
	if (!config->north_texture_path || !config->south_texture_path
		|| !config->west_texture_path || !config->east_texture_path)
	{
		printf("Error: Missing texture paths\n");
		return (0);
	}
	if (config->floor_r == -1 || config->ceiling_r == -1)
	{
		printf("Error: Missing floor or ceiling colors\n");
		return (0);
	}
	if (config->map_height == 0)
	{
		printf("Error: No map found\n");
		return (0);
	}
	return (1);
}
