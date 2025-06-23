#ifndef BASIC1_H
# define BASIC1_H

#include <mlx.h>
#include <stdio.h>

#define WIDTH 300
#define HEIGHT 300

typedef struct s_data
{
	void	*mlx; //mlx connection
	void	*win; //window to display on
	void	*img; //image to display
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

#endif 