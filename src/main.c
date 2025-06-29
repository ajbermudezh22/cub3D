/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:04:38 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 14:18:52 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = (char *)data->addr + (y * data->line_len + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

static void	init_program(t_data *data)
{
	init_mlx(data);
	init_textures(data);
}

static void	cleanup_program(t_data *data)
{
	free_textures(data->mlx, &data->texture);
	free_config(&data->config);
	if (data->map.grid)
		free(data->map.grid);
}

static void	print_controls(void)
{
	printf("Controls:\n");
	printf("W/S - Move forward/backward\n");
	printf("A/D - Turn left/right\n");
	printf("Arrow Keys - Turn left/right\n");
	printf("ESC - Exit program\n");
	printf("SPACE - Switch view modes\n");
}

int	main(int argc, char **argv)
{
	t_data	img;

	// Initialize the data structure
	img.map.grid = NULL;
	if (argc != 2)
	{
		printf("Usage: %s <path_to_map.cub>\n", argv[0]);
		return (1);
	}
	if (!parse_cub_file(argv[1], &img.config))
	{
		printf("Error: Failed to parse .cub file\n");
		return (1);
	}
	setup_map_from_config(&img);
	init_program(&img);
	render_complete_view(&img);
	print_controls();
	mlx_hook(img.win, 2, 1L << 0, key_hook, &img);
	mlx_hook(img.win, 17, 1L << 17, close_window, &img);
	mlx_loop(img.mlx);
	cleanup_program(&img);
	return (0);
}
