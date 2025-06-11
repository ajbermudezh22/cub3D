#ifndef MINILIBX_1_H
# define MINILIBX_1_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 300
#define HEIGHT 300

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
} t_data;


#endif