/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:43:07 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/30 07:59:39 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

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
# define FOV 60              // Field of view in degrees
# define NUM_RAYS 500        // Number of rays for 3D rendering
# define WALL_HEIGHT 200     // Wall height in 3D view

typedef struct s_config
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
	char	**map_grid;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_config;

typedef struct s_texture
{
	void	*north_texture;
	void	*south_texture;
	void	*west_texture;
	void	*east_texture;
	int		tex_width;
	int		tex_height;
	int		*north_addr;
	int		*south_addr;
	int		*west_addr;
	int		*east_addr;
	int		floor_color;
	int		ceiling_color;
}	t_texture;

typedef struct s_line
{
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;
	float	dx;
	float	dy;
	float	steps;
	int		thickness;
	int		color;
}	t_line;

typedef struct s_ray
{
	float	angle;
	float	px;
	float	py;
	float	dx;
	float	dy;
	float	delta_dist_x;
	float	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	int		side;
	float	perp_wall_dist;
}	t_ray;

typedef struct s_wall
{
	int		x;
	float	distance;
	float	wall_height_f;
	float	wall_start_f;
	float	wall_end_f;
	int		wall_start;
	int		wall_end;
	float	shade_factor;
}	t_wall;

typedef struct s_thick_line_params
{
	float	dx;
	float	dy;
	float	steps;
	float	x;
	float	y;
}	t_thick_line_params;

typedef struct s_draw_ray_line_params
{
	float	dx;
	float	dy;
	float	steps;
	float	x;
	float	y;
}	t_draw_ray_line_params;

typedef struct s_draw_line_params
{
	float	end_x;
	float	end_y;
	int		thickness;
}	t_draw_line_params;

typedef struct s_ray_params
{
	int		num_rays;
	float	fov;
	float	start_angle;
	float	ray_angle;
	int		hit_x;
	int		hit_y;
	float	distance;
	int		color;
}	t_ray_params;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	int			*map;
	int			map_s;
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
}	t_data;

typedef struct s_ray_result
{
	float	distance;
	int		wall_side;
	float	wall_x;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray_result;

// antialiasing.c
void	draw_antialiased_edges(t_data *data, t_wall *wall);

// draw.c
void	cast_and_draw_ray(t_data *data, t_ray_params *p, int i);
void	draw_rays_2d(t_data *data);
void	draw_player_2d(t_data *data);

// draw_utils.c
void	draw_direction_line(t_data *data);
void	draw_thick_line(t_data *data, t_draw_line_params *line_params);
void	draw_player_circle(t_data *data);

// main.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	cleanup_program(t_data *data);

// map.c
float	get_player_angle(char dir);
void	setup_map_from_config(t_data *data);
void	draw_map_2d(t_data *data);
int		is_wall(t_data *data, int x, int y);
void	draw_cell(t_data *data, int x, int y, int color);
void	render_complete_view(t_data *data);
void	draw_separator(t_data *data);
int		key_hook(int keycode, t_data *data);
int		close_hook(t_data *data);

// parser_config.c
int	check_config_complete(t_config *config);
void	init_config(t_config *config);

// parser.c
int		parse_cub_file(char *filename, t_config *config);
void	free_config(t_config *config);
int		parse_color(char *line, int *r, int *g, int *b);
int		parse_texture_path(char *line, char **path, char *cub_file_dir);
int		validate_map(t_config *config);
void	find_player_position(t_config *config);

// parser_utils.c
int	process_line(char *line, t_config *config, char *cub_file_dir,
	int *map_started);

// parser_map.c
int	read_map(char *line, t_config *config, char ***temp_map, int *map_lines);
void	copy_and_pad_map(t_config *config, char **temp_map, int map_lines);


// raycaster.c
float	cast_ray_2d(t_data *data, float ray_angle, int *hit_x, int *hit_y);
void	draw_player_circle(t_data *data);
void	draw_hit_point(t_data *data, int hit_x, int hit_y);
void	draw_ray_line(t_data *data, int hit_x, int hit_y, int color);
float	calculate_distance(t_data *data, float current_x, float current_y);
int		check_wall_hit(t_data *data, float current_x, float current_y);

// render3d.c
float	cast_ray_3d(t_data *data, float ray_angle);
void	draw_wall_slice(t_data *data, int x, float distance, int wall_color);
int		blend_colors(int color1, int color2, float alpha);
void	render_3d_view(t_data *data);
void	clear_3d_view(t_data *data);
void	clear_2d_view(t_data *data);

// Raycasting functions
void	init_ray(t_data *data, t_ray *ray, float ray_angle);
void	perform_dda(t_data *data, t_ray *ray);

// Wall rendering functions
void	init_wall(t_data *data, t_wall *wall, int x, float distance);
void	draw_ceiling(t_data *data, t_wall *wall);
void	draw_floor(t_data *data, t_wall *wall);
void	draw_textured_wall(t_data *data, t_wall *wall);
void	draw_antialiased_edges(t_data *data, t_wall *wall);

// texture.c
int		load_textures(void *mlx, t_texture *tex, char *north_path,
			char *south_path, char *west_path, char *east_path);
void	free_textures(void *mlx, t_texture *tex);
void	set_floor_ceiling_colors(t_texture *tex, int floor_r, int floor_g,
			int floor_b, int ceiling_r, int ceiling_g, int ceiling_b);
int		get_texture_pixel(t_texture *tex, int wall_side, int tex_x, int tex_y);
void	draw_textured_wall_slice(t_data *data, int screen_x,
			t_ray_result ray_result, t_texture *tex, int screen_height,
			int map_width);
t_ray_result	cast_ray_with_texture_info(t_data *data, float ray_angle);
void	render_3d_view_textured(t_data *data, t_texture *tex);

// wall_render.c
void	draw_ceiling(t_data *data, t_wall *wall);
void	draw_floor(t_data *data, t_wall *wall);
void	draw_textured_wall(t_data *data, t_wall *wall);

// window.c
void	init_textures(t_data *data);
void	init_mlx(t_data *data);

#endif