#ifndef TEXTURE_H
# define TEXTURE_H

#include <mlx.h>
#include <math.h>
#include <stdio.h>

// Forward declaration to avoid circular dependency
typedef struct s_data t_data;

// Texture-related data structure
typedef struct s_texture
{
    void    *north_texture;
    void    *south_texture; 
    void    *west_texture;
    void    *east_texture;
    int     tex_width;
    int     tex_height;
    int     *north_addr;
    int     *south_addr;
    int     *west_addr;
    int     *east_addr;
    int     floor_color;    // RGB color for floor
    int     ceiling_color;  // RGB color for ceiling
} t_texture;

// Ray result structure for texture mapping
typedef struct s_ray_result
{
    float   distance;
    int     wall_side;      // 0=North, 1=South, 2=West, 3=East
    float   wall_x;         // X position where ray hit wall (for texture mapping)
    int     step_x;         // Direction of ray
    int     step_y;         // Direction of ray
    int     side;           // 0 if x-side, 1 if y-side
} t_ray_result;

// Function prototypes
int     load_textures(void *mlx, t_texture *tex, char *north_path, char *south_path, 
                     char *west_path, char *east_path);
void    free_textures(void *mlx, t_texture *tex);
void    set_floor_ceiling_colors(t_texture *tex, int floor_r, int floor_g, int floor_b,
                                int ceiling_r, int ceiling_g, int ceiling_b);
int     get_texture_pixel(t_texture *tex, int wall_side, int tex_x, int tex_y);
void    draw_textured_wall_slice(t_data *data, int screen_x, t_ray_result ray_result, 
                               t_texture *tex, int screen_height, int map_width);

#endif