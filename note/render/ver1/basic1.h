#ifndef MINILIBX_1_H
# define MINILIBX_1_H

#include <mlx.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1000          // Increased width for split view
#define HEIGHT 500
#define MAP_WIDTH 500       // Left half for 2D map
#define VIEW_WIDTH 500      // Right half for 3D view
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_UP 65362
#define KEY_DOWN 65364

// 3D rendering constants
#define FOV 60              // Field of view in degrees
#define NUM_RAYS 500        // Number of rays for 3D rendering
#define WALL_HEIGHT 200     // Wall height in 3D view

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	float	player_angle;
	float	player_dx;
	float	player_dy;
	int		view_mode;      // 0 = 2D only, 1 = split view, 2 = 3D only
} t_data;

// Function declarations
void my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif