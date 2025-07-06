/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 07:34:35 by albermud          #+#    #+#             */
/*   Updated: 2025/07/06 07:35:24 by albermud         ###   ########.fr       */
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

int	validate_map(t_config *config)
{
	int		x;
	int		y;
	char	c;

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
