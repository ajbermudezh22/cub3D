/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:19 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/29 10:00:00 by albbermu         ###   ########.fr       */
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

int	parse_color(char *line, int *r, int *g, int *b)
{
	char	*line_copy;
	char	*token;
	int		result;

	line_copy = strdup(line);
	if (!line_copy)
		return (0);
	token = strtok(line_copy, " \t");
	if (!token)
		return (free(line_copy), 0);
	token = strtok(NULL, ",");
	if (!token)
		return (free(line_copy), 0);
	*r = atoi(token);
	token = strtok(NULL, ",");
	if (!token)
		return (free(line_copy), 0);
	*g = atoi(token);
	token = strtok(NULL, " \t\n");
	if (!token)
		return (free(line_copy), 0);
	*b = atoi(token);
	result = (*r >= 0 && *r <= 255 && *g >= 0 && *g <= 255
			&& *b >= 0 && *b <= 255);
	return (free(line_copy), result);
}

int	parse_cub_file(char *filename, t_config *config)
{
	printf("Error: Parser needs to be implemented\n");
	printf("File: %s\n", filename);
	(void)config;
	return (0);
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
		i = -1;
		while (++i < config->map_height)
		{
			if (config->map_grid[i])
				free(config->map_grid[i]);
		}
		free(config->map_grid);
	}
}
