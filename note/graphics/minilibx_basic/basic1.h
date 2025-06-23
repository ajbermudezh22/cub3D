#ifndef MINILIBX_1_H
# define MINILIBX_1_H

#include <mlx.h>
#include <stdio.h>

#define WIDTH 500
#define HEIGHT 500

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
} t_data;


#endif