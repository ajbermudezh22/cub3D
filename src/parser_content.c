/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:49:40 by albermud          #+#    #+#             */
/*   Updated: 2025/07/06 18:53:48 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	process_single_line(char *line, t_config *config,
		char *cub_file_dir, t_parser_state *state)
{
	int	ret;

	if (line[0] == '\n' || line[0] == '\0')
		return (1);
	ret = process_line(line, config, cub_file_dir, &state->map_started);
	if (ret == 0)
		return (0);
	if (ret == 2)
	{
		if (!read_map(line, config, &state->temp_map, &state->map_lines))
			return (0);
	}
	return (1);
}

static int	read_and_process_lines(int fd, t_config *config,
		char *cub_file_dir, t_parser_state *state)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!process_single_line(line, config, cub_file_dir, state))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_file_content(int fd, t_config *config, char *cub_file_dir)
{
	t_parser_state	state;

	state.temp_map = NULL;
	state.map_lines = 0;
	state.map_started = 0;
	if (!read_and_process_lines(fd, config, cub_file_dir, &state))
		return (0);
	copy_and_pad_map(config, state.temp_map, state.map_lines);
	return (1);
}

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

int	process_line(char *line, t_config *config, char *cub_file_dir,
	int *map_started)
{
	char	**tokens;
	int		result;

	tokens = prepare_tokens(line);
	if (!tokens)
		return (1);
	if (!tokens[0])
	{
		ft_free_split(tokens);
		return (1);
	}
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
