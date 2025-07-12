/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:04:38 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/30 18:11:41 by albermud         ###   ########.fr       */
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

void	cleanup_program(t_data *data)
{
	if (data->map)
		free(data->map);
	free_textures(data->mlx, &data->texture);
	free_config(&data->config);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

static void	print_controls(void)
{
	printf("Controls:\n");
	printf("W/S - Move forward/backward\n");
	printf("A/D - Move left/right\n");
	printf("←/→ - Turn left/right\n");
	printf("ESC - Exit program\n");
	printf("SPACE - Switch view modes\n");
}

int	main(int argc, char **argv)
{
	t_data	img;

	memset(&img, 0, sizeof(t_data));
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
	mlx_hook(img.win, 17, 0L, close_hook, &img);
	mlx_loop(img.mlx);
	cleanup_program(&img);
	return (0);
}
