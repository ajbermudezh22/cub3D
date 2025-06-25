#ifndef MINILIBX_1_H
# define MINILIBX_1_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1000
#define HEIGHT 1000

#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

typedef struct s_player
{
	int		x;
	int		y;
	int		size;
} t_player;

typedef struct s_data
{
	void		*mlx; //mlx connection
	void		*win; //window to display on
	void		*img; //image to display
	int			*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	t_player	*player;
} t_data;

#endif