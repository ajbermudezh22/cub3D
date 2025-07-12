/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:19 by albermud          #+#    #+#             */
/*   Updated: 2025/07/06 18:56:00 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_parsed_data(t_config *config)
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
	if (!find_and_validate_player_position(config))
		return (0);
	if (!validate_map(config))
		return (0);
	return (1);
}

static int	parse_content(int fd, t_config *config, char *filename)
{
	char	*cub_file_dir;
	char	*last_slash;

	cub_file_dir = ft_strdup(filename);
	if (!cub_file_dir)
		return (0);
	last_slash = ft_strrchr(cub_file_dir, '/');
	if (last_slash)
		*last_slash = '\0';
	else
		ft_strcpy(cub_file_dir, ".");
	if (!parse_file_content(fd, config, cub_file_dir))
	{
		free(cub_file_dir);
		return (0);
	}
	free(cub_file_dir);
	return (1);
}

static int	check_and_open_file(char *filename)
{
	int	fd;
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		printf("Error: Invalid file extension. Must be .cub\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (-1);
	}
	return (fd);
}

int	parse_cub_file(char *filename, t_config *config)
{
	int	fd;

	fd = check_and_open_file(filename);
	if (fd < 0)
		return (0);
	init_config(config);
	if (!parse_content(fd, config, filename))
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!validate_parsed_data(config))
		return (0);
	config->map_grid[config->player_y][config->player_x] = '0';
	return (1);
}

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
