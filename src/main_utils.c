/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:00:00 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/29 10:00:00 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_program(t_data *data)
{
	init_mlx(data);
	init_textures(data);
}

void	cleanup_program(t_data *data)
{
	free_textures(data->mlx, &data->texture);
	free_config(&data->config);
	if (data->map.grid)
		free(data->map.grid);
}

void	print_controls(void)
{
	printf("Controls:\n");
	printf("W - Move forward\n");
	printf("S - Move backward\n");
	printf("A - Strafe left\n");
	printf("D - Strafe right\n");
	printf("Left/Right Arrow Keys - Turn left/right\n");
	printf("SPACE - Switch view modes\n");
	printf("ESC - Exit program\n");
}

int	check_and_init(int argc, char **argv, t_data *img)
{
	img->map.grid = NULL;
	if (argc != 2)
	{
		printf("Usage: %s <path_to_map.cub>\n", argv[0]);
		return (1);
	}
	if (!parse_cub_file(argv[1], &img->config))
	{
		printf("Error: Failed to parse .cub file\n");
		return (1);
	}
	return (0);
}
