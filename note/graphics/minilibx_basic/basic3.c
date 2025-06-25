#include "basic1.h"
#include <mlx.h>
#include <math.h>
#define PI 3.141592

int mapX = 8, mapY = 8, mapS = 64;
int map[] = {
    1,1,1,1,1,1,1,1,
    1,0,0,0,1,0,0,1,
    1,0,0,0,1,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,0,0,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1
};

void init(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D_window");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, 
                                          &data->line_len, &data->endian);
    
    // Initialize player direction vectors
    data->player_dx = cos(data->player_angle);
    data->player_dy = sin(data->player_angle);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        char *dst = (char *)data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

void draw_map(t_data *data)
{
    int x, y, cell_size = 64;
    
    for (y = 0; y < mapY; y++) {
        for (x = 0; x < mapX; x++) {
            int color = (map[y * mapX + x] == 1) ? 0xFFFFFF : 0x333333;
            int px = x * cell_size;
            int py = y * cell_size;
            
            // Draw cell
            for (int cell_y = py; cell_y < py + cell_size; cell_y++) {
                for (int cell_x = px; cell_x < px + cell_size; cell_x++) {
                    if (cell_x < WIDTH && cell_y < HEIGHT) {
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

// **NEW: Ray casting function**
float cast_ray(t_data *data, float ray_angle, int *hit_x, int *hit_y)
{
    float dx = cos(ray_angle);
    float dy = sin(ray_angle);
    
    float current_x = data->player_x;
    float current_y = data->player_y;
    
    // Step along the ray
    float step_size = 0.5;  // Small steps for accuracy
    
    while (1) {
        current_x += dx * step_size;
        current_y += dy * step_size;
        
        // Check bounds
        if (current_x < 0 || current_x >= WIDTH || current_y < 0 || current_y >= HEIGHT) {
            break;
        }
        
        // Check if we hit a wall
        int map_x = (int)current_x / mapS;
        int map_y = (int)current_y / mapS;
        
        if (map_x >= 0 && map_x < mapX && map_y >= 0 && map_y < mapY) {
            if (map[map_y * mapX + map_x] == 1) {
                *hit_x = (int)current_x;
                *hit_y = (int)current_y;
                
                // Calculate distance
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

// **NEW: Draw multiple rays for visualization**
void draw_rays(t_data *data)
{
    int num_rays = 60;  // Number of rays to cast
    float fov = PI / 3; // 60 degrees field of view
    float start_angle = data->player_angle - fov / 2;
    
    for (int i = 0; i < num_rays; i++) {
        float ray_angle = start_angle + (fov * i / num_rays);
        int hit_x, hit_y;
        float distance = cast_ray(data, ray_angle, &hit_x, &hit_y);
        (void)distance;
        // Draw ray line
        float dx = hit_x - data->player_x;
        float dy = hit_y - data->player_y;
        float steps = fmax(fabs(dx), fabs(dy));
        
        if (steps > 0) {
            dx /= steps;
            dy /= steps;
            
            float x = data->player_x;
            float y = data->player_y;
            
            for (int step = 0; step < (int)steps; step++) {
                // Color rays differently - main ray is bright, others are dim
                int color = (i == num_rays / 2) ? 0x00FF00 : 0x004400;
                my_mlx_pixel_put(data, (int)x, (int)y, color);
                x += dx;
                y += dy;
            }
        }
        
        // Draw hit point
        my_mlx_pixel_put(data, hit_x, hit_y, 0xFF0000);
        my_mlx_pixel_put(data, hit_x-1, hit_y, 0xFF0000);
        my_mlx_pixel_put(data, hit_x+1, hit_y, 0xFF0000);
        my_mlx_pixel_put(data, hit_x, hit_y-1, 0xFF0000);
        my_mlx_pixel_put(data, hit_x, hit_y+1, 0xFF0000);
    }
}

void draw_player(t_data *data)
{
    int size = 8;
    
    // Draw player circle
    for (int y = -size; y <= size; y++) {
        for (int x = -size; x <= size; x++) {
            if (x*x + y*y <= size*size) {
                my_mlx_pixel_put(data, data->player_x + x, data->player_y + y, 0xFFFF00);
            }
        }
    }
    
    // Draw direction line (longer and more visible)
    int line_length = 30;
    float end_x = data->player_x + data->player_dx * line_length;
    float end_y = data->player_y + data->player_dy * line_length;
    
    // Draw thick direction line
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
            
            for (int step = 0; step < (int)steps; step++) {
                my_mlx_pixel_put(data, (int)x, (int)y, 0xFF0000);
                x += dx;
                y += dy;
            }
        }
    }
}

void clear_window(t_data *data)
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            my_mlx_pixel_put(data, x, y, 0x222222);  // Dark gray background
        }
    }
}

int is_wall(int x, int y)
{
    int map_x = x / mapS;
    int map_y = y / mapS;
    
    if (map_x < 0 || map_x >= mapX || map_y < 0 || map_y >= mapY)
        return 1;
    return map[map_y * mapX + map_x];
}

// **FIXED: Proper FPS-style movement**
int key_hook(int keycode, t_data *data)
{
    int move_speed = 5;
    float rotation_speed = 0.1;  // Radians per key press
    
    float new_x = data->player_x;
    float new_y = data->player_y;
    float new_angle = data->player_angle;
    
    // Movement (W/S = forward/backward, A/D = rotate left/right)
    if (keycode == 'w' || keycode == 'W') {
        // Move forward in the direction we're facing
        new_x += data->player_dx * move_speed;
        new_y += data->player_dy * move_speed;
    }
    if (keycode == 's' || keycode == 'S') {
        // Move backward from the direction we're facing
        new_x -= data->player_dx * move_speed;
        new_y -= data->player_dy * move_speed;
    }
    if (keycode == 'a' || keycode == 'A') {
        // Rotate left
        new_angle += rotation_speed;
    }
    if (keycode == 'd' || keycode == 'D') {
        // Rotate right
        new_angle -= rotation_speed;
    }
    
    // Collision detection for movement
    if (!is_wall((int)new_x, (int)new_y) && 
        new_x >= 10 && new_x < WIDTH-10 && new_y >= 10 && new_y < HEIGHT-10) {
        data->player_x = new_x;
        data->player_y = new_y;
    }
    
    // Update angle and direction vectors
    data->player_angle = new_angle;
    data->player_dx = cos(data->player_angle);
    data->player_dy = sin(data->player_angle);
    
    // Redraw everything
    clear_window(data);
    draw_map(data);
    draw_rays(data);  // **NEW: Draw rays**
    draw_player(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    
    return (0);
}

int main()
{
    t_data img;
    
    init(&img);
    
    // Start player in center of a open area
    img.player_x = 200;
    img.player_y = 200;
    img.player_angle = 0;  // Facing right
    img.player_dx = cos(img.player_angle);
    img.player_dy = sin(img.player_angle);
    
    // Initial draw
    clear_window(&img);
    draw_map(&img);
    draw_rays(&img);
    draw_player(&img);
    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    
    mlx_hook(img.win, 2, 1L<<0, key_hook, &img);
    mlx_loop(img.mlx);
    return (0);
}
