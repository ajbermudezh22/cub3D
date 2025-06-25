#ifndef MINILIBX_1_H
# define MINILIBX_1_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //open()

#define WIDTH 1000
#define HEIGHT 1000

#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_DOWN 65364

#define MAP_TILE_SIZE 20

typedef struct s_map
{
	char		**grid;	//2d to store
	int			width;	//width in tiles
	int			height;	//height in tiles
}t_map;

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
	t_map		*map;
} t_data;


//* * * * init_window.c * * * *
void	init_player(t_player *player);
void	init_window(t_data *data);
void	clear_screen(t_data *data);
void	update_display(t_data *data);
int		close_window(t_data *data);

//* * * * player.c * * * *
int		key_press(int keycode, t_data *data);
void	draw_player(t_data *data);

//* * * * main.c * * * *
int		main();

#endif