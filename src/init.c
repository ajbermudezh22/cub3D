/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:56:52 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/26 15:57:27 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D - 2D/3D View");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, 
                                          &data->line_len, &data->endian);
    
    // Initialize player direction vectors
    data->player_dx = cos(data->player_angle);
    data->player_dy = sin(data->player_angle);
    data->view_mode = 1; // Start with split view
}

