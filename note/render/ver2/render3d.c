#include "basic1.h"
#include <math.h>

#define PI 3.141592
#define DR 0.0174533  // One degree in radians (PI/180)

// External map variables from main file
extern int mapX, mapY, mapS;
extern int map[];

// Enhanced DDA raycasting algorithm for smoother, more accurate distance calculation
float cast_ray_3d(t_data *data, float ray_angle)
{
	// Normalize angle
	while (ray_angle < 0) ray_angle += 2 * PI;
	while (ray_angle >= 2 * PI) ray_angle -= 2 * PI;
	
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
	int map_x = (int)(px / mapS);
	int map_y = (int)(py / mapS);
	
	// Calculate step and initial side_dist
	int step_x, step_y;
	float side_dist_x, side_dist_y;
	
	if (dx < 0) {
		step_x = -1;
		side_dist_x = (px / mapS - map_x) * delta_dist_x;
	} else {
		step_x = 1;
		side_dist_x = (map_x + 1.0f - px / mapS) * delta_dist_x;
	}
	
	if (dy < 0) {
		step_y = -1;
		side_dist_y = (py / mapS - map_y) * delta_dist_y;
	} else {
		step_y = 1;
		side_dist_y = (map_y + 1.0f - py / mapS) * delta_dist_y;
	}
	
	// Perform DDA
	int hit = 0;
	int side; // 0 for x-side, 1 for y-side
	
	while (hit == 0) {
		// Jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y) {
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		} else {
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		
		// Check if ray has hit a wall
		if (map_x < 0 || map_x >= mapX || map_y < 0 || map_y >= mapY || 
			map[map_y * mapX + map_x] == 1) {
			hit = 1;
		}
	}
	
	// Calculate distance
	float perp_wall_dist;
	if (side == 0) {
		perp_wall_dist = (map_x - px / mapS + (1 - step_x) / 2) / dx;
	} else {
		perp_wall_dist = (map_y - py / mapS + (1 - step_y) / 2) / dy;
	}
	
	// Convert to pixel distance and apply fisheye correction
	float distance = perp_wall_dist * mapS;
	float angle_diff = ray_angle - data->player_angle;
	distance = distance * cos(angle_diff);
	
	return distance;
}

// Smooth wall rendering with anti-aliasing and texture effects
void draw_wall_slice(t_data *data, int x, float distance, int wall_color)
{
	(void)wall_color;
	if (distance <= 0) distance = 1; // Prevent division by zero
	
	// Use float precision for smoother calculations
	float wall_height_f = (WALL_HEIGHT * mapS) / distance;
	float wall_start_f = (HEIGHT / 2.0f) - (wall_height_f / 2.0f);
	float wall_end_f = (HEIGHT / 2.0f) + (wall_height_f / 2.0f);
	
	// Calculate integer bounds for main rendering
	int wall_start = (int)wall_start_f;
	int wall_end = (int)wall_end_f;
	
	// Clamp to screen bounds
	if (wall_start < 0) wall_start = 0;
	if (wall_end >= HEIGHT) wall_end = HEIGHT - 1;
	
	// Base shading calculation
	float shade_factor = 1.0f - (distance / 400.0f); // Smoother distance falloff
	if (shade_factor < 0.1f) shade_factor = 0.1f;
	if (shade_factor > 1.0f) shade_factor = 1.0f;
	
	// Draw ceiling with gradient
	for (int y = 0; y < wall_start; y++) {
		// Ceiling gradient - darker towards horizon
		float ceiling_factor = (float)y / wall_start_f;
		int ceiling_shade = (int)(0x44 * (0.3f + 0.7f * ceiling_factor));
		int ceiling_color = (ceiling_shade << 8) | ceiling_shade; // Blue-ish
		my_mlx_pixel_put(data, MAP_WIDTH + x, y, ceiling_color);
	}
	
	// Anti-aliasing for top edge
	if (wall_start_f > 0 && wall_start_f < HEIGHT) {
		float alpha = wall_start_f - (int)wall_start_f;
		if (alpha > 0 && wall_start > 0) {
			// Blend ceiling and wall colors
			int ceiling_color = 0x001144;
			int wall_base = (int)(180 * shade_factor);
			int blended = blend_colors(ceiling_color, wall_base << 16 | wall_base << 8 | wall_base, alpha);
			my_mlx_pixel_put(data, MAP_WIDTH + x, wall_start - 1, blended);
		}
	}
	
	// Draw wall with texture effect
	for (int y = wall_start; y <= wall_end && y < HEIGHT; y++) {
		// Calculate position along wall height (0.0 to 1.0)
		float wall_pos = (float)(y - wall_start_f) / wall_height_f;
		
		// Base wall color with distance shading
		int base_shade = (int)(180 * shade_factor);
		
		// Add texture variation based on position
		float texture_variation = 1.0f;
		
		// Horizontal bands for brick-like effect
		float band_pos = fmod(wall_pos * 8.0f, 1.0f);
		if (band_pos < 0.1f || band_pos > 0.9f) {
			texture_variation *= 0.85f; // Darker mortar lines
		}
		
		// Vertical variation based on x position
		float vertical_variation = 1.0f + 0.1f * sin(x * 0.3f);
		texture_variation *= vertical_variation;
		
		// Slight random variation for roughness
		float noise = 1.0f + 0.05f * sin(x * 0.7f + wall_pos * 15.0f);
		texture_variation *= noise;
		
		// Apply texture to base color
		int final_shade = (int)(base_shade * texture_variation);
		if (final_shade < 0) final_shade = 0;
		if (final_shade > 255) final_shade = 255;
		
		// Create RGB color (slight warm tint)
		int r = final_shade;
		int g = (int)(final_shade * 0.95f);
		int b = (int)(final_shade * 0.9f);
		
		int final_color = (r << 16) | (g << 8) | b;
		my_mlx_pixel_put(data, MAP_WIDTH + x, y, final_color);
	}
	
	// Anti-aliasing for bottom edge
	if (wall_end_f < HEIGHT - 1 && wall_end_f > 0) {
		float alpha = (int)(wall_end_f + 1) - wall_end_f;
		if (alpha > 0 && wall_end < HEIGHT - 1) {
			// Blend wall and floor colors
			int wall_base = (int)(180 * shade_factor);
			int wall_color_blend = wall_base << 16 | wall_base << 8 | wall_base;
			int floor_color = 0x003300;
			int blended = blend_colors(wall_color_blend, floor_color, alpha);
			my_mlx_pixel_put(data, MAP_WIDTH + x, wall_end + 1, blended);
		}
	}
	
	// Draw floor with perspective shading
	for (int y = wall_end + 1; y < HEIGHT; y++) {
		// Floor gets darker with distance from wall
		float floor_distance = (float)(y - wall_end) / (HEIGHT - wall_end);
		float floor_shade = 0.3f - (floor_distance * 0.2f);
		if (floor_shade < 0.05f) floor_shade = 0.05f;
		
		// Add checkerboard pattern
		int checker_x = (x + (int)(distance * 0.1f)) / 32;
		int checker_y = (int)(distance + y * 2) / 32;
		if ((checker_x + checker_y) % 2) {
			floor_shade *= 1.2f;
		}
		
		int floor_green = (int)(0x33 * floor_shade);
		int floor_color = floor_green << 8;
		my_mlx_pixel_put(data, MAP_WIDTH + x, y, floor_color);
	}
}

// Color blending function for anti-aliasing
int blend_colors(int color1, int color2, float alpha)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;
	
	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;
	
	int r = (int)(r1 * (1.0f - alpha) + r2 * alpha);
	int g = (int)(g1 * (1.0f - alpha) + g2 * alpha);
	int b = (int)(b1 * (1.0f - alpha) + b2 * alpha);
	
	return (r << 16) | (g << 8) | b;
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

// Function to clear 2D view area
void clear_2d_view(t_data *data)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			my_mlx_pixel_put(data, x, y, 0x222222);
		}
	}
}