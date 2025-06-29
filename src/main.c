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
		*(unsigned int *)dst = color;
	}
}

int	main(int argc, char **argv)
{
	t_data	img;

	if (check_and_init(argc, argv, &img))
		return (1);
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
