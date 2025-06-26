/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:42:40 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/26 15:55:29 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
{
    t_data img;
    
    init(&img);
    
    // Start player in center of open area
    img.player_x = 200;
    img.player_y = 200;
    img.player_angle = 0;
    img.player_dx = cos(img.player_angle);
    img.player_dy = sin(img.player_angle);
    
    // Initial render
    render_complete_view(&img);
    
    printf("Controls:\n");
    printf("W/S - Move forward/backward\n");
    printf("A/D - Turn left/right\n");
    printf("SPACE - Switch view modes\n");
    
    mlx_hook(img.win, 2, 1L<<0, key_hook, &img);
    mlx_loop(img.mlx);
    return (0);
}
