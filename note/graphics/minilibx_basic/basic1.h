#ifndef MINILIBX_1_H
# define MINILIBX_1_H

#include <mlx.h>
#include <stdio.h>

#define WIDTH 500
#define HEIGHT 500
#define KEY_ESC 65307
#define KEY_LEFT 65361  // Left arrow key
#define KEY_RIGHT 65363 // Right arrow key
#define KEY_UP 65362    // Up arrow key
#define KEY_DOWN 65364  // Down arrow key

//

typedef struct s_data
{
	void	*mlx; //mlx connection
	void	*win; //window to display on
	void	*img; //image to display
	int		*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	float	player_angle;
	float	player_dx; //direction vector
	float	player_dy;
} t_data;


#endif