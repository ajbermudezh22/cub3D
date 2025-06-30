/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 07:35:10 by albermud          #+#    #+#             */
/*   Updated: 2025/06/30 07:23:43 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_char(char *str, char c)
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

static int	process_and_validate_colors(char **split, int *r, int *g, int *b)
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
	int		i;

	i = 1;
	while (line[i] == ' ')
		i++;
	trimmed_line = ft_strtrim(line + i, " \t\n");
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
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	trimmed_path = ft_strtrim(line + i, " \t\n");
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

int	process_line(char *line, t_config *config, char *cub_file_dir,
	int *map_started)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture_path(line, &config->north_texture_path,
				cub_file_dir));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture_path(line, &config->south_texture_path,
				cub_file_dir));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture_path(line, &config->west_texture_path,
				cub_file_dir));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_path(line, &config->east_texture_path,
				cub_file_dir));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line, &config->floor_r, &config->floor_g,
				&config->floor_b));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line, &config->ceiling_r, &config->ceiling_g,
				&config->ceiling_b));
	else if (line[0] == '1' || line[0] == '0' || ft_strchr(line, 'N')
		|| ft_strchr(line, 'S') || ft_strchr(line, 'E') || ft_strchr(line, 'W'))
	{
		*map_started = 1;
		return (2);
	}
	return (1);
}
