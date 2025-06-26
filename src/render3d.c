/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:12:19 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/26 16:13:30 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float cast_ray_3d(t_data *data, float ray_angle)
{
    // Normalize angle
    if (ray_angle < 0) ray_angle += 2 * PI;
    if (ray_angle > 2 * PI) ray_angle -= 2 * PI;
    
    // Player position in map coordinates
    float px = data->player_x;
    float py = data->player_y;
    
    // Ray direction
    float rx = cos(ray_angle);
    float ry = sin(ray_angle);
    
    // Current position
    float x = px;
    float y = py;
    
    // Step size (small for accuracy)
    float step = 0.5;
    
    while (1) {
        x += rx * step;
        y += ry * step;
        
        // Convert to map coordinates
        int mx = (int)(x / mapS);
        int my = (int)(y / mapS);
        
        // Check bounds
        if (mx < 0 || mx >= mapX || my < 0 || my >= mapY) {
            break;
        }
        
        // Check for wall hit
        if (map[my * mapX + mx] == 1) {
            // Calculate distance
            float distance = sqrt((x - px) * (x - px) + (y - py) * (y - py));
            
            // Fix fisheye effect by multiplying by cos of angle difference
            float angle_diff = ray_angle - data->player_angle;
            distance = distance * cos(angle_diff);
            
            return distance;
        }
    }
    
    // Return maximum distance if no wall hit
    return 1000;
}

void draw_wall_slice(t_data *data, int x, float distance, int wall_color)
{
    if (distance <= 0) distance = 1; // Prevent division by zero
    
    // Calculate wall height based on distance
    int wall_height = (int)(WALL_HEIGHT * mapS / distance);
    
    // Calculate wall start and end points
    int wall_start = (HEIGHT / 2) - (wall_height / 2);
    int wall_end = (HEIGHT / 2) + (wall_height / 2);
    
    // Clamp to screen bounds
    if (wall_start < 0) wall_start = 0;
    if (wall_end >= HEIGHT) wall_end = HEIGHT - 1;
    
    // Draw ceiling (dark blue)
    for (int y = 0; y < wall_start; y++) {
        my_mlx_pixel_put(data, MAP_WIDTH + x, y, 0x001144);
    }
    
    // Draw wall with shading based on distance
    int shade = (int)(255 - (distance * 255 / 300)); // Adjust 300 for fade distance
    if (shade < 0) shade = 0;
    if (shade > 255) shade = 255;
    
    int shaded_color = (shade << 16) | (shade << 8) | shade; // Grayscale
    if (wall_color != 0xFFFFFF) { // If colored wall
        shaded_color = wall_color;
    }
    
    for (int y = wall_start; y <= wall_end; y++) {
        my_mlx_pixel_put(data, MAP_WIDTH + x, y, shaded_color);
    }
    
    // Draw floor (dark green)
    for (int y = wall_end + 1; y < HEIGHT; y++) {
        my_mlx_pixel_put(data, MAP_WIDTH + x, y, 0x003300);
    }
}

// Main 3D rendering function
void render_3d_view(t_data *data)
{
    float fov = FOV * DR; // Convert FOV to radians
    float start_angle = data->player_angle - (fov / 2);
    
    for (int x = 0; x < VIEW_WIDTH; x++) {
        // Calculate ray angle for this screen column
        float ray_angle = start_angle + (fov * x / VIEW_WIDTH);
        
        // Cast ray and get distance
        float distance = cast_ray_3d(data, ray_angle);
        
        // Draw wall slice
        draw_wall_slice(data, x, distance, 0xFFFFFF);
    }
}

// Clear the 3D view area
void clear_3d_view(t_data *data)
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = MAP_WIDTH; x < WIDTH; x++) {
            my_mlx_pixel_put(data, x, y, 0x000000);
        }
    }
}
