/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:34 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 15:38:52 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int load_textures(void *mlx, t_texture *tex, char *north_path, char *south_path, 
                 char *west_path, char *east_path)
{
    int bits_per_pixel, line_len, endian;
    
    // Initialize all texture pointers to NULL
    tex->north_texture = NULL;
    tex->south_texture = NULL;
    tex->west_texture = NULL;
    tex->east_texture = NULL;
    
    printf("Loading textures from .cub file:\n");
    
    // Load North texture
    tex->north_texture = mlx_xpm_file_to_image(mlx, north_path, &tex->tex_width, &tex->tex_height);
    if (!tex->north_texture) {
        printf("Error: Failed to load north texture: %s\n", north_path);
        return 0;
    }
    tex->north_addr = (int *)mlx_get_data_addr(tex->north_texture, &bits_per_pixel, &line_len, &endian);
    printf("✓ North texture loaded: %s\n", north_path);
    
    // Load South texture
    tex->south_texture = mlx_xpm_file_to_image(mlx, south_path, &tex->tex_width, &tex->tex_height);
    if (!tex->south_texture) {
        printf("Error: Failed to load south texture: %s\n", south_path);
        return 0;
    }
    tex->south_addr = (int *)mlx_get_data_addr(tex->south_texture, &bits_per_pixel, &line_len, &endian);
    printf("✓ South texture loaded: %s\n", south_path);
    
    // Load West texture
    tex->west_texture = mlx_xpm_file_to_image(mlx, west_path, &tex->tex_width, &tex->tex_height);
    if (!tex->west_texture) {
        printf("Error: Failed to load west texture: %s\n", west_path);
        return 0;
    }
    tex->west_addr = (int *)mlx_get_data_addr(tex->west_texture, &bits_per_pixel, &line_len, &endian);
    printf("✓ West texture loaded: %s\n", west_path);
    
    // Load East texture
    tex->east_texture = mlx_xpm_file_to_image(mlx, east_path, &tex->tex_width, &tex->tex_height);
    if (!tex->east_texture) {
        printf("Error: Failed to load east texture: %s\n", east_path);
        return 0;
    }
    tex->east_addr = (int *)mlx_get_data_addr(tex->east_texture, &bits_per_pixel, &line_len, &endian);
    printf("✓ East texture loaded: %s\n", east_path);
    
    printf("All textures loaded successfully! Size: %dx%d\n", tex->tex_width, tex->tex_height);
    return 1;
}

// Free all loaded textures
void free_textures(void *mlx, t_texture *tex)
{
    if (tex->north_texture)
        mlx_destroy_image(mlx, tex->north_texture);
    if (tex->south_texture)
        mlx_destroy_image(mlx, tex->south_texture);
    if (tex->west_texture)
        mlx_destroy_image(mlx, tex->west_texture);
    if (tex->east_texture)
        mlx_destroy_image(mlx, tex->east_texture);
}

// Set floor and ceiling colors from RGB values
void set_floor_ceiling_colors(t_texture *tex, int floor_r, int floor_g, int floor_b,
                             int ceiling_r, int ceiling_g, int ceiling_b)
{
    tex->floor_color = (floor_r << 16) | (floor_g << 8) | floor_b;
    tex->ceiling_color = (ceiling_r << 16) | (ceiling_g << 8) | ceiling_b;
}

// Get a pixel from the appropriate texture
int get_texture_pixel(t_texture *tex, int wall_side, int tex_x, int tex_y)
{
    int *texture_addr;
    
    // Clamp texture coordinates
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex->tex_width) tex_x = tex->tex_width - 1;
    if (tex_y < 0) tex_y = 0;
    if (tex_y >= tex->tex_height) tex_y = tex->tex_height - 1;
    
    // Select texture based on wall side
    switch(wall_side) {
        case 0: texture_addr = tex->north_addr; break;
        case 1: texture_addr = tex->south_addr; break;
        case 2: texture_addr = tex->west_addr; break;
        case 3: texture_addr = tex->east_addr; break;
        default: texture_addr = tex->north_addr; break;
    }
    
    if (!texture_addr)
        return 0xFF0000; // Red color if texture not loaded
    
    return texture_addr[tex_y * tex->tex_width + tex_x];
}

// Enhanced ray casting that returns wall side information
t_ray_result cast_ray_with_texture_info(t_data *data, float ray_angle)
{
    t_ray_result result;
    
    // Normalize angle
    while (ray_angle < 0) ray_angle += 2 * M_PI;
    while (ray_angle >= 2 * M_PI) ray_angle -= 2 * M_PI;
    
    // Player position in world coordinates
    float px = data->player_x;
    float py = data->player_y;
    
    // Ray direction
    float dx = cos(ray_angle);
    float dy = sin(ray_angle);
    
    // DDA algorithm variables
    float delta_dist_x = fabs(1.0f / dx);
    float delta_dist_y = fabs(1.0f / dy);
    
    // Current map position
    int map_x = (int)(px / data->map.tile_size);
    int map_y = (int)(py / data->map.tile_size);
    
    // Calculate step and initial side_dist
    float side_dist_x, side_dist_y;
    
    if (dx < 0) {
        result.step_x = -1;
        side_dist_x = (px / data->map.tile_size - map_x) * delta_dist_x;
    } else {
        result.step_x = 1;
        side_dist_x = (map_x + 1.0f - px / data->map.tile_size) * delta_dist_x;
    }
    
    if (dy < 0) {
        result.step_y = -1;
        side_dist_y = (py / data->map.tile_size - map_y) * delta_dist_y;
    } else {
        result.step_y = 1;
        side_dist_y = (map_y + 1.0f - py / data->map.tile_size) * delta_dist_y;
    }
    
    // Perform DDA
    int hit = 0;
    
    while (hit == 0) {
        // Jump to next map square, either in x-direction, or in y-direction
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += result.step_x;
            result.side = 0;
        } else {
            side_dist_y += delta_dist_y;
            map_y += result.step_y;
            result.side = 1;
        }
        
        // Check if ray has hit a wall
        if (map_x < 0 || map_x >= data->map.width || map_y < 0 || map_y >= data->map.height || 
            data->map.grid[map_y * data->map.width + map_x] == 1) {
            hit = 1;
        }
    }
    
    // Calculate distance
    float perp_wall_dist;
    if (result.side == 0) {
        perp_wall_dist = (map_x - px / data->map.tile_size + (1 - result.step_x) / 2) / dx;
        result.wall_x = py / data->map.tile_size + perp_wall_dist * dy;
    } else {
        perp_wall_dist = (map_y - py / data->map.tile_size + (1 - result.step_y) / 2) / dy;
        result.wall_x = px / data->map.tile_size + perp_wall_dist * dx;
    }
    result.wall_x -= floor(result.wall_x);
    
    // Determine wall side for texture selection
    if (result.side == 0) {
        if (result.step_x > 0)
            result.wall_side = 2; // West wall
        else
            result.wall_side = 3; // East wall
    } else {
        if (result.step_y > 0)
            result.wall_side = 0; // North wall
        else
            result.wall_side = 1; // South wall
    }
    
    // Convert to pixel distance and apply fisheye correction
    result.distance = perp_wall_dist * data->map.tile_size;
    // float angle_diff = ray_angle - data->player_angle;
    // result.distance = result.distance * cos(angle_diff);
    
    return result;
}

// Draw a textured wall slice
void draw_textured_wall_slice(t_data *data, int screen_x, t_ray_result ray_result, 
                             t_texture *tex, int screen_height, int map_width)
{
    if (ray_result.distance <= 0) ray_result.distance = 1; // Prevent division by zero
    
    // Calculate wall height
    float wall_height_f = (WALL_HEIGHT * data->map.tile_size) / ray_result.distance;
    int wall_start = (screen_height / 2) - (wall_height_f / 2);
    int wall_end = (screen_height / 2) + (wall_height_f / 2);
    
    // Clamp to screen bounds
    if (wall_start < 0) wall_start = 0;
    if (wall_end >= screen_height) wall_end = screen_height - 1;
    
    // Calculate texture X coordinate
    int tex_x = (int)(ray_result.wall_x * tex->tex_width);
    if (ray_result.side == 0 && ray_result.step_x > 0) tex_x = tex->tex_width - tex_x - 1;
    if (ray_result.side == 1 && ray_result.step_y < 0) tex_x = tex->tex_width - tex_x - 1;
    
    // Draw ceiling
    for (int y = 0; y < wall_start; y++) {
        my_mlx_pixel_put(data, map_width + screen_x, y, tex->ceiling_color);
    }
    
    // Draw textured wall
    for (int y = wall_start; y <= wall_end; y++) {
        // Calculate texture Y coordinate
        int tex_y = (int)(((float)(y - wall_start) / (wall_end - wall_start)) * tex->tex_height);
        
        // Get pixel color from texture
        int color = get_texture_pixel(tex, ray_result.wall_side, tex_x, tex_y);
        
        // Apply distance shading
        float shade = 1.0f - (ray_result.distance / 400.0f);
        if (shade < 0.1f) shade = 0.1f;
        if (shade > 1.0f) shade = 1.0f;
        
        int r = ((color >> 16) & 0xFF) * shade;
        int g = ((color >> 8) & 0xFF) * shade;
        int b = (color & 0xFF) * shade;
        
        int final_color = (r << 16) | (g << 8) | b;
        my_mlx_pixel_put(data, map_width + screen_x, y, final_color);
    }
    
    // Draw floor
    for (int y = wall_end + 1; y < screen_height; y++) {
        my_mlx_pixel_put(data, map_width + screen_x, y, tex->floor_color);
    }
}

// Main 3D rendering function with textures
void render_3d_view_textured(t_data *data, t_texture *tex)
{
    float fov = FOV * (M_PI / 180.0f); // Convert FOV to radians
    float start_angle = data->player_angle - (fov / 2);
    
    for (int x = 0; x < VIEW_WIDTH; x++) {
        // Calculate ray angle for this screen column
        float ray_angle = start_angle + (fov * x / VIEW_WIDTH);
        
        // Cast ray and get result with texture info
        t_ray_result ray_result = cast_ray_with_texture_info(data, ray_angle);
        
        // Draw textured wall slice
        draw_textured_wall_slice(data, x, ray_result, tex, HEIGHT, MAP_WIDTH);
    }
}
