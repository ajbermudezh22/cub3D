/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:19 by albermud          #+#    #+#             */
/*   Updated: 2025/06/30 07:25:21 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_file_content(FILE *file, t_config *config, char *cub_file_dir)
{
	char	line[1024];
	int		map_started;
	int		map_lines;
	char	**temp_map;
	int		ret;

	map_started = 0;
	map_lines = 0;
	temp_map = NULL;
	while (fgets(line, sizeof(line), file))
	{
		if (line[0] == '\n' || line[0] == '\0')
			continue ;
		ret = process_line(line, config, cub_file_dir, &map_started);
		if (ret == 0)
			return (0);
		if (ret == 2)
		{
			if (!read_map(line, config, &temp_map, &map_lines))
				return (0);
		}
	}
	copy_and_pad_map(config, temp_map, map_lines);
	return (1);
}

static int	validate_parsed_data(t_config *config)
{
	if (!check_config_complete(config))
		return (0);
	find_player_position(config);
	if (!validate_map(config))
	{
		printf("Error: Invalid map\n");
		return (0);
	}
	return (1);
}

static int	parse_content(FILE *file, t_config *config, char *filename)
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
	if (!parse_file_content(file, config, cub_file_dir))
	{
		free(cub_file_dir);
		return (0);
	}
	free(cub_file_dir);
	return (1);
}

int	parse_cub_file(char *filename, t_config *config)
{
	FILE	*file;

	file = fopen(filename, "r");
	if (!file)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (0);
	}
	init_config(config);
	if (!parse_content(file, config, filename))
	{
		fclose(file);
		return (0);
	}
	fclose(file);
	if (!validate_parsed_data(config))
		return (0);
	return (1);
}
