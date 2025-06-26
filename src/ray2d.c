/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:59:20 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/26 16:36:39 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float cast_ray_2d(t_data *data, float ray_angle, int *hit_x, int *hit_y)
{
    float dx = cos(ray_angle);
    float dy = sin(ray_angle);
    
    float current_x = data->player_x;
    float current_y = data->player_y;
    
    float step_size = 0.5;
    
    while (1) {
        current_x += dx * step_size;
        current_y += dy * step_size;
        
        if (current_x < 0 || current_x >= MAP_WIDTH || current_y < 0 || current_y >= HEIGHT) {
            break;
        }
        
        int map_x = (int)current_x / mapS;
        int map_y = (int)current_y / mapS;
        
        if (map_x >= 0 && map_x < mapX && map_y >= 0 && map_y < mapY) {
            if (map[map_y * mapX + map_x] == 1) {
                *hit_x = (int)current_x;
                *hit_y = (int)current_y;
                
                float distance = sqrt(pow(current_x - data->player_x, 2) + 
                                    pow(current_y - data->player_y, 2));
                return distance;
            }
        }
    }
    
    *hit_x = (int)current_x;
    *hit_y = (int)current_y;
    return sqrt(pow(current_x - data->player_x, 2) + pow(current_y - data->player_y, 2));
}
