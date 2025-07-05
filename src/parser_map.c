/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 07:40:10 by albermud          #+#    #+#             */
/*   Updated: 2025/07/05 17:18:46 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	find_and_validate_player_position(t_config *config)
{
	int	y;
	int	x;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < config->map_width)
		{
			if (ft_strchr("NSEW", config->map_grid[y][x]))
			{
				if (player_count == 0)
				{
					config->player_x = x;
					config->player_y = y;
					config->player_dir = config->map_grid[y][x];
				}
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count == 0)
	{
		printf("Error: No player start position found in map.\n");
		return (0);
	}
	if (player_count > 1)
	{
		printf("Error: Multiple player start positions found in map.\n");
		return (0);
	}
	return (1);
}

static int	is_valid_cell(t_config *config, int y, int x)
{
	if (y == 0 || y == config->map_height - 1 || x == 0
		|| x == config->map_width - 1)
		return (0);
	if (config->map_grid[y - 1][x] == ' ')
		return (0);
	if (config->map_grid[y + 1][x] == ' ')
		return (0);
	if (config->map_grid[y][x - 1] == ' ')
		return (0);
	if (config->map_grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

int	validate_map(t_config *config)
{
	int	x;
	int	y;
	char c;

	if (!config->map_grid || config->map_height == 0 || config->map_width == 0)
		return (0);
	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < config->map_width)
		{
			c = config->map_grid[y][x];
			if (!ft_strchr("01NSEW ", c))
			{
				printf("Error: Invalid character '%c' in map.\n", c);
				return (0);
			}
			if (c == '0' || ft_strchr("NSEW", c))
			{
				if (!is_valid_cell(config, y, x))
				{
					printf("Error: Map is not enclosed by walls.\n");
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	read_map(char *line, t_config *config, char ***temp_map, int *map_lines)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, "\n");
	*temp_map = ft_realloc(*temp_map, sizeof(char *) * (*map_lines),
			sizeof(char *) * (*map_lines + 1));
	if (!*temp_map)
	{
		free(trimmed_line);
		return (0);
	}
	(*temp_map)[*map_lines] = trimmed_line;
	if ((int)ft_strlen(trimmed_line) > config->map_width)
		config->map_width = ft_strlen(trimmed_line);
	(*map_lines)++;
	return (1);
}

void	copy_and_pad_map(t_config *config, char **temp_map, int map_lines)
{
	int		i;
	int		j;
	int		len;

	config->map_height = map_lines;
	config->map_grid = malloc(sizeof(char *) * config->map_height);
	i = 0;
	while (i < map_lines)
	{
		config->map_grid[i] = malloc(config->map_width + 1);
		ft_strcpy(config->map_grid[i], temp_map[i]);
		len = ft_strlen(config->map_grid[i]);
		j = len;
		while (j < config->map_width)
		{
			config->map_grid[i][j] = ' ';
			j++;
		}
		config->map_grid[i][config->map_width] = '\0';
		free(temp_map[i]);
		i++;
	}
	free(temp_map);
}
