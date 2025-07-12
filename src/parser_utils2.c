/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 07:34:35 by albermud          #+#    #+#             */
/*   Updated: 2025/07/06 07:42:59 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_player(t_config *config, int y, int x, int *player_count)
{
	if (ft_strchr("NSEW", config->map_grid[y][x]))
	{
		if (*player_count == 0)
		{
			config->player_x = x;
			config->player_y = y;
			config->player_dir = config->map_grid[y][x];
		}
		(*player_count)++;
	}
}

static int	find_player_in_map(t_config *config)
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
			check_player(config, y, x, &player_count);
			x++;
		}
		y++;
	}
	return (player_count);
}

int	find_and_validate_player_position(t_config *config)
{
	int	player_count;

	player_count = find_player_in_map(config);
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

static int	check_cell(t_config *config, int y, int x)
{
	char	c;

	c = config->map_grid[y][x];
	if (!ft_strchr("01NSEW ", c))
	{
		printf("Error: Invalid character '%c' in map.\n", c);
		return (0);
	}
	if (c == '0' || ft_strchr("NSEW", c))
	{
		if (y == 0 || y == config->map_height - 1 || x == 0
			|| x == config->map_width - 1
			|| config->map_grid[y - 1][x] == ' '
			|| config->map_grid[y + 1][x] == ' '
			|| config->map_grid[y][x - 1] == ' '
			|| config->map_grid[y][x + 1] == ' ')
		{
			printf("Error: Map is not enclosed by walls.\n");
			return (0);
		}
	}
	return (1);
}

int	validate_map(t_config *config)
{
	int		x;
	int		y;

	if (!config->map_grid || config->map_height == 0 || config->map_width == 0)
		return (0);
	y = 0;
	while (y < config->map_height)
	{
		x = 0;
		while (x < config->map_width)
		{
			if (!check_cell(config, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
