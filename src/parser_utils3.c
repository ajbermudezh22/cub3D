/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 07:44:34 by albermud          #+#    #+#             */
/*   Updated: 2025/07/06 07:50:02 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_config_line(char **tokens, t_config *config,
		char *cub_file_dir)
{
	if (ft_strcmp(tokens[0], "NO") == 0)
		return (parse_texture_path(tokens[1], &config->north_texture_path,
				cub_file_dir));
	if (ft_strcmp(tokens[0], "SO") == 0)
		return (parse_texture_path(tokens[1], &config->south_texture_path,
				cub_file_dir));
	if (ft_strcmp(tokens[0], "WE") == 0)
		return (parse_texture_path(tokens[1], &config->west_texture_path,
				cub_file_dir));
	if (ft_strcmp(tokens[0], "EA") == 0)
		return (parse_texture_path(tokens[1], &config->east_texture_path,
				cub_file_dir));
	if (ft_strcmp(tokens[0], "F") == 0)
		return (parse_color(tokens[1], &config->floor_r, &config->floor_g,
				&config->floor_b));
	if (ft_strcmp(tokens[0], "C") == 0)
		return (parse_color(tokens[1], &config->ceiling_r, &config->ceiling_g,
				&config->ceiling_b));
	return (-1);
}

static int	is_map_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	return (line[i] == '1' || line[i] == '0' || ft_strchr(line, 'N')
		|| ft_strchr(line, 'S') || ft_strchr(line, 'E')
		|| ft_strchr(line, 'W'));
}

static char	**tokenize_line(char *line)
{
	char	*trimmed_line;
	char	**tokens;

	trimmed_line = ft_strtrim(line, " \t\n");
	if (!trimmed_line || !*trimmed_line)
	{
		if (trimmed_line)
			free(trimmed_line);
		return (NULL);
	}
	tokens = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!tokens || !tokens[0])
	{
		ft_free_split(tokens);
		return (NULL);
	}
	return (tokens);
}

int	process_line(char *line, t_config *config, char *cub_file_dir,
	int *map_started)
{
	char	**tokens;
	int		result;

	tokens = tokenize_line(line);
	if (!tokens)
		return (1);
	result = parse_config_line(tokens, config, cub_file_dir);
	if (result != -1)
	{
		ft_free_split(tokens);
		return (result);
	}
	if (is_map_line(line))
	{
		*map_started = 1;
		ft_free_split(tokens);
		return (2);
	}
	ft_free_split(tokens);
	return (1);
}
