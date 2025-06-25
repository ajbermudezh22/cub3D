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

// Function declarations for 3D rendering (from render3d.c)
void render_3d_view(t_data *data);
void clear_3d_view(t_data *data);
void clear_2d_view(t_data *data);

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

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        char *dst = (char *)data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
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

// Original ray casting for 2D visualization
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

// Draw separator line between 2D and 3D views
void draw_separator(t_data *data)
{
    for (int y = 0; y < HEIGHT; y++) {
        my_mlx_pixel_put(data, MAP_WIDTH, y, 0xFFFFFF);
        my_mlx_pixel_put(data, MAP_WIDTH - 1, y, 0xFFFFFF);
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

void render_complete_view(t_data *data)
{
    // Clear both views
    clear_2d_view(data);
    clear_3d_view(data);
    
    // Render 2D view (left half)
    draw_map_2d(data);
    draw_rays_2d(data);
    draw_player_2d(data);
    
    // Draw separator
    draw_separator(data);
    
    // Render 3D view (right half)
    render_3d_view(data);
    
    // Update display
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int key_hook(int keycode, t_data *data)
{
    int move_speed = 5;
    float rotation_speed = 0.1;
    
    float new_x = data->player_x;
    float new_y = data->player_y;
    float new_angle = data->player_angle;
    
    // Movement controls
    if (keycode == 'w' || keycode == 'W') {
        new_x += data->player_dx * move_speed;
        new_y += data->player_dy * move_speed;
    }
    if (keycode == 's' || keycode == 'S') {
        new_x -= data->player_dx * move_speed;
        new_y -= data->player_dy * move_speed;
    }
    if (keycode == 'a' || keycode == 'A') {
        new_angle += rotation_speed;
    }
    if (keycode == 'd' || keycode == 'D') {
        new_angle -= rotation_speed;
    }
    
    // View mode switching
    if (keycode == ' ') { // Spacebar to switch views
        data->view_mode = (data->view_mode + 1) % 3;
    }
    
    // Collision detection
    if (!is_wall((int)new_x, (int)new_y) && 
        new_x >= 10 && new_x < MAP_WIDTH-10 && new_y >= 10 && new_y < HEIGHT-10) {
        data->player_x = new_x;
        data->player_y = new_y;
    }
    
    // Update angle and direction
    data->player_angle = new_angle;
    data->player_dx = cos(data->player_angle);
    data->player_dy = sin(data->player_angle);
    
    // Render based on view mode
    render_complete_view(data);
    
    return (0);
}

int main()
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