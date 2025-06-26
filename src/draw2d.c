/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:06:44 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/26 16:18:54 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void clear_2d_view(t_data *data)
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            my_mlx_pixel_put(data, x, y, 0x222222);
        }
    }
}

void draw_map_2d(t_data *data)
{
    int x, y, cell_size = 64;
    
    for (y = 0; y < mapY; y++) {
        for (x = 0; x < mapX; x++) {
            int color = (map[y * mapX + x] == 1) ? 0xFFFFFF : 0x333333;
            int px = x * cell_size;
            int py = y * cell_size;
            
            // Only draw within 2D view area
            if (px < MAP_WIDTH && py < HEIGHT) {
                // Draw cell
                for (int cell_y = py; cell_y < py + cell_size && cell_y < HEIGHT; cell_y++) {
                    for (int cell_x = px; cell_x < px + cell_size && cell_x < MAP_WIDTH; cell_x++) {
                        // Add grid lines for better visualization
                        if (cell_x == px || cell_y == py) {
                            my_mlx_pixel_put(data, cell_x, cell_y, 0x666666);
                        } else {
                            my_mlx_pixel_put(data, cell_x, cell_y, color);
                        }
                    }
                }
            }
        }
    }
}


void draw_rays_2d(t_data *data)
{
    int num_rays = 60;
    float fov = PI / 3;
    float start_angle = data->player_angle - fov / 2;
    
    for (int i = 0; i < num_rays; i++) {
        float ray_angle = start_angle + (fov * i / num_rays);
        int hit_x, hit_y;
        float distance = cast_ray_2d(data, ray_angle, &hit_x, &hit_y);
        (void)distance;
        
        // Only draw rays within 2D view area
        if (hit_x < MAP_WIDTH) {
            float dx = hit_x - data->player_x;
            float dy = hit_y - data->player_y;
            float steps = fmax(fabs(dx), fabs(dy));
            
            if (steps > 0) {
                dx /= steps;
                dy /= steps;
                
                float x = data->player_x;
                float y = data->player_y;
                
                for (int step = 0; step < (int)steps && x < MAP_WIDTH; step++) {
                    int color = (i == num_rays / 2) ? 0x00FF00 : 0x004400;
                    my_mlx_pixel_put(data, (int)x, (int)y, color);
                    x += dx;
                    y += dy;
                }
            }
            
            // Draw hit point
            if (hit_x < MAP_WIDTH) {
                my_mlx_pixel_put(data, hit_x, hit_y, 0xFF0000);
                my_mlx_pixel_put(data, hit_x-1, hit_y, 0xFF0000);
                my_mlx_pixel_put(data, hit_x+1, hit_y, 0xFF0000);
                my_mlx_pixel_put(data, hit_x, hit_y-1, 0xFF0000);
                my_mlx_pixel_put(data, hit_x, hit_y+1, 0xFF0000);
            }
        }
    }
}

void draw_player_2d(t_data *data)
{
    int size = 8;
    
    // Only draw if player is in 2D view area
    if (data->player_x < MAP_WIDTH) {
        // Draw player circle
        for (int y = -size; y <= size; y++) {
            for (int x = -size; x <= size; x++) {
                if (x*x + y*y <= size*size) {
                    int px = data->player_x + x;
                    int py = data->player_y + y;
                    if (px < MAP_WIDTH) {
                        my_mlx_pixel_put(data, px, py, 0xFFFF00);
                    }
                }
            }
        }
        
        // Draw direction line
        int line_length = 30;
        float end_x = data->player_x + data->player_dx * line_length;
        float end_y = data->player_y + data->player_dy * line_length;
        
        for (int thickness = -2; thickness <= 2; thickness++) {
            float perpendicular_x = -data->player_dy * thickness;
            float perpendicular_y = data->player_dx * thickness;
            
            float dx = end_x - data->player_x;
            float dy = end_y - data->player_y;
            float steps = fmax(fabs(dx), fabs(dy));
            
            if (steps > 0) {
                dx /= steps;
                dy /= steps;
                
                float x = data->player_x + perpendicular_x;
                float y = data->player_y + perpendicular_y;
                
                for (int step = 0; step < (int)steps && x < MAP_WIDTH; step++) {
                    my_mlx_pixel_put(data, (int)x, (int)y, 0xFF0000);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
}

void draw_separator(t_data *data)
{
    for (int y = 0; y < HEIGHT; y++) {
        my_mlx_pixel_put(data, MAP_WIDTH, y, 0xFFFFFF);
        my_mlx_pixel_put(data, MAP_WIDTH - 1, y, 0xFFFFFF);
    }
}
