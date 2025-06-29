/* ************************************************************************** */
/*																			*/
/*														:::	 ::::::::  */
/*  cub3d.h											:+:	 :+:	:+:  */
/*													+:+ +:+		 +:+	 */
/*  By: albbermu <albbermu@student.42.fr>		 +#+ +:+	  +#+		*/
/*												+#+#+#+#+#+  +#+		  */
/*  Created: 2025/06/04 13:43:07 by albbermu		 #+#	#+#			 */
/*  Updated: 2025/06/27 15:27:14 by albbermu		 ###  ########.fr	  */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <limits.h>
# include <math.h>

# define WIDTH 1000
# define HEIGHT 500
# define MAP_WIDTH 500
# define VIEW_WIDTH 500
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define PI 3.141592
# define DR 0.0174533
# define M_PI 3.14159265358979323846
# define TILE_SIZE 64

// 3D rendering constants
# define FOV 60			 // Field of view in degrees
# define NUM_RAYS 500		// Number of rays for 3D rendering
# define WALL_HEIGHT 200	 // Wall height in 3D view

typedef struct s_config
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	int	 floor_r;
	int	 floor_g;
	int	 floor_b;
	int	 ceiling_r;
	int	 ceiling_g;
	int	 ceiling_b;
	char	**map_grid;
	int	 map_width;
	int	 map_height;
	int	 player_x;
	int	 player_y;
	char	player_dir;
} t_config;

typedef struct s_texture
{
	void	*north_texture;
	void	*south_texture; 
	void	*west_texture;
	void	*east_texture;
	int	 tex_width;
	int	 tex_height;
	int	 *north_addr;
	int	 *south_addr;
	int	 *west_addr;
	int	 *east_addr;
	int	 floor_color;
	int	 ceiling_color;
} t_texture;

typedef struct s_map
{
	int		*grid;
	int		width;
	int		height;
	int		tile_size;
} t_map;

typedef struct s_buffer_check
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
}	t_buffer_check;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	float		player_angle;
	float		player_dx;
	float		player_dy;
	int			view_mode;
	t_texture	texture;
	t_config	config;
	t_map		map;
} t_data;

typedef struct s_ray_result
{
	float  distance;
	int	 wall_side;
	float  wall_x;
	int	 step_x;
	int	 step_y;
	int	 side;
} t_ray_result;

// main.c
void my_mlx_pixel_put(t_data *data, int x, int y, int color);

// map.c
float	get_player_angle(char dir);
void	setup_map_from_config(t_data *data);
int		is_wall_with_buffer(t_data *data, float x, float y, float buffer);

// map_utils.c 
void	allocate_map_grid(t_data *data);
void	fill_map_grid(t_data *data);
int		check_buffer_bounds(t_data *data, t_buffer_check *check);
int		check_buffer_walls(t_data *data, t_buffer_check *check);

// map_render.c
void	draw_cell(t_data *data, int x, int y, int color);
void	draw_map_2d(t_data *data);
void	setup_player_position(t_data *data);

// main_utils.c
void	init_program(t_data *data);
void	cleanup_program(t_data *data);
void	print_controls(void);
int		check_and_init(int argc, char **argv, t_data *img);

// parser.c
int		parse_cub_file(char *filename, t_config *config);
void	free_config(t_config *config);
int		parse_color(char *line, int *r, int *g, int *b);
void	init_config(t_config *config);

// raycaster.c
float	cast_ray_2d(t_data *data, float ray_angle, int *hit_x, int *hit_y);
void	draw_rays_2d(t_data *data);
void	draw_player_2d(t_data *data);

// render3d.c
float	cast_ray_3d(t_data *data, float ray_angle);
void	draw_wall_slice(t_data *data, int x, float distance, int wall_color);
int		blend_colors(int color1, int color2, float alpha);
void	render_3d_view(t_data *data);
void	clear_3d_view(t_data *data);
void	clear_2d_view(t_data *data);

// texture.c
int	 load_textures(void *mlx, t_texture *tex, char *north_path, char *south_path, 
					 char *west_path, char *east_path);
void	free_textures(void *mlx, t_texture *tex);
void	set_floor_ceiling_colors(t_texture *tex, int floor_r, int floor_g, int floor_b,
								int ceiling_r, int ceiling_g, int ceiling_b);
int	 get_texture_pixel(t_texture *tex, int wall_side, int tex_x, int tex_y);
t_ray_result cast_ray_with_texture_info(t_data *data, float ray_angle);
void	draw_textured_wall_slice(t_data *data, int screen_x, t_ray_result ray_result, 
							  t_texture *tex, int screen_height, int map_width);
void	render_3d_view_textured(t_data *data, t_texture *tex);
							  
// window.c
void	init_mlx(t_data *data);
void	init_textures(t_data *data);
void	render_complete_view(t_data *data);
void	draw_separator(t_data *data);
int		key_hook(int keycode, t_data *data);
int		close_window(t_data *data);

// window_helpers.c
void	update_player_position(t_data *data, float new_x, float new_y);
void	update_player_angle(t_data *data, float new_angle);
void	handle_movement(int keycode, t_data *data, float *new_x, float *new_y);
void	handle_rotation(int keycode, float *new_angle);

// Function prototypes (raycast_draw.c)
void	draw_thick_line(t_data *data, float end_x, float end_y, int thickness);
void	draw_rays_2d(t_data *data);
void	draw_player_2d(t_data *data);

#endif