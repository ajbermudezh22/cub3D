/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 07:35:10 by albermud          #+#    #+#             */
/*   Updated: 2025/07/06 07:45:36 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_char(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	process_and_validate_colors(char **split, int *r, int *g, int *b)
{
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		ft_free_split(split);
		return (0);
	}
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	ft_free_split(split);
	if (*r < 0 || *r > 255)
		return (0);
	if (*g < 0 || *g > 255)
		return (0);
	if (*b < 0 || *b > 255)
		return (0);
	return (1);
}

int	parse_color(char *line, int *r, int *g, int *b)
{
	char	**split;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n");
	if (!trimmed_line)
		return (0);
	if (count_char(trimmed_line, ',') != 2)
	{
		free(trimmed_line);
		return (0);
	}
	split = ft_split(trimmed_line, ',');
	free(trimmed_line);
	if (!process_and_validate_colors(split, r, g, b))
		return (0);
	return (1);
}

int	parse_texture_path(char *line, char **path, char *cub_file_dir)
{
	char	*trimmed_path;
	char	*tmp;

	trimmed_path = ft_strtrim(line, " \t\n");
	if (!trimmed_path)
		return (0);
	if (trimmed_path[0] != '/')
	{
		tmp = ft_strjoin(cub_file_dir, "/");
		*path = ft_strjoin(tmp, trimmed_path);
		free(tmp);
	}
	else
		*path = ft_strdup(trimmed_path);
	free(trimmed_path);
	if (!*path)
		return (0);
	return (1);
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
