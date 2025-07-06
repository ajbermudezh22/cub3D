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
