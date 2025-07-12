/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:43:07 by albbermu          #+#    #+#             */
/*   Updated: 2025/07/06 19:23:39 by albermud         ###   ########.fr       */
/*                                                                            */
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
# define FOV 60              // Field of view in degrees
# define NUM_RAYS 500        // Number of rays for 3D rendering
# define WALL_HEIGHT 200     // Wall height in 3D view
# define VIEW_DISTANCE 400   // Shading distance

typedef struct s_texture_raycast_vars
{
	float	px;
	float	py;
	float	dx;
	float	dy;
	float	delta_dist_x;
	float	delta_dist_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	int		hit;
	float	perp_wall_dist;
}	t_raycast;

typedef struct s_texture_wall_vars
{
	float	wall_height_f;
	int		wall_start;
	int		wall_end;
	int		tex_x;
	int		y;
	int		tex_y;
	int		color;
	float	shade_factor;
	int		r;
	int		g;
	int		b;
}	t_texture_wall_vars;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_parser_state
{
	char	**temp_map;
	int		map_lines;
	int		map_started;
}				t_parser_state;

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

typedef struct s_texture_details
{
	char	*name;
	char	*path;
	void	**texture;
	int		**addr;
}	t_texture_details;

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

typedef struct s_line_iter
{
	float	dx;
	float	dy;
	float	steps;
	float	x;
	float	y;
}	t_line_iter;

typedef struct s_line_params
{
	float	end_x;
	float	end_y;
	int		thickness;
}	t_line_params;

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
	int			win_width;
	int			win_height;
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

typedef struct s_wall_pixel_params
{
	t_data			*data;
	int				screen_x;
	t_ray_result	ray_result;
	t_texture		*tex;
}	t_wall_pixel_params;

// antialiasing.c
void			draw_antialiased_edges(t_data *data, t_wall *wall);

// draw.c
void			cast_and_draw_ray(t_data *data, t_ray_params *p, int i);
void			draw_rays_2d(t_data *data);
void			draw_player_2d(t_data *data);

// utils.c
int				is_wall(t_data *data, int x, int y);
void			draw_map_2d(t_data *data);
void			init_line_params(t_data *data, t_line_params *line_params,
					t_line_iter *p);
void			render_texture_ceiling(t_texture_wall_vars *vars, t_data *data,
					int screen_x, t_texture *tex);
void			render_texture_floor(t_texture_wall_vars *vars, t_data *data,
					int screen_x, t_texture *tex);
// draw_utils.c
void			draw_direction_line(t_data *data);
void			draw_thick_line(t_data *data, t_line_params *line_params);
void			draw_player_circle(t_data *data);

// main.c
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			cleanup_program(t_data *data);

// map.c
float			get_player_angle(char dir);
void			setup_map_from_config(t_data *data);
void			draw_cell(t_data *data, int x, int y, int color);

// parser_config.c
int				check_config_complete(t_config *config);
void			init_config(t_config *config);

// parser.c
int				parse_cub_file(char *filename, t_config *config);
void			free_config(t_config *config);
int				parse_color(char *line, int *r, int *g, int *b);
int				parse_texture_path(char *line, char **path, char *cub_file_dir);

// parser_content.c
int				parse_file_content(int fd, t_config *config,
					char *cub_file_dir);

// parser_utils.c
int				count_char(char *str, char c);
int				process_and_validate_colors(char **split, int *r, int *g,
					int *b);
int				parse_color(char *line, int *r, int *g, int *b);
int				parse_texture_path(char *line, char **path, char *cub_file_dir);

// parser_utils2.c
int				find_and_validate_player_position(t_config *config);
int				validate_map(t_config *config);

// parser_utils3.c
int				process_line(char *line, t_config *config, char *cub_file_dir,
					int *map_started);

// parser_map.c
int				read_map(char *line, t_config *config, char ***temp_map,
					int *map_lines);
void			copy_and_pad_map(t_config *config, char **temp_map,
					int map_lines);
int				is_valid_cell(t_config *config, int y, int x);
int				is_map_line(char *line);
char			**prepare_tokens(char *line);

// raycaster.c
float			cast_ray_2d(t_data *data, float ray_angle, int *hit_x,
					int *hit_y);
void			draw_player_circle(t_data *data);
void			draw_hit_point(t_data *data, int hit_x, int hit_y);
void			draw_ray_line(t_data *data, int hit_x, int hit_y, int color);
float			calculate_distance(t_data *data, float current_x,
					float current_y);
int				check_wall_hit(t_data *data, float current_x, float current_y);

// render.c
void			draw_wall_slice(t_data *data, int x, float distance,
					int wall_color);
void			render_3d_view(t_data *data);
void			clear_3d_view(t_data *data);
void			clear_2d_view(t_data *data);

// raycast.c
float			cast_ray_3d(t_data *data, float ray_angle);
int				blend_colors(int color1, int color2, float alpha);

// Raycasting functions
void			init_ray(t_data *data, t_ray *ray, float ray_angle);
void			perform_dda(t_data *data, t_ray *ray);

// Wall rendering functions
void			init_wall(t_data *data, t_wall *wall, int x, float distance);
void			draw_ceiling(t_data *data, t_wall *wall);
void			draw_floor(t_data *data, t_wall *wall);
void			draw_textured_wall(t_data *data, t_wall *wall);
void			draw_antialiased_edges(t_data *data, t_wall *wall);

// texture.c
int				load_textures(t_data *data);
void			set_floor_ceiling_colors(t_texture *tex, t_config *config);
void			free_textures(void *mlx, t_texture *tex);
int				get_texture_pixel(t_texture *tex, int wall_side, int tex_x,
					int tex_y);
void			draw_textured_wall_slice(t_data *data, int screen_x,
					t_ray_result ray_result, t_texture *tex);
t_ray_result	cast_ray_with_texture_info(t_data *data, float ray_angle);
void			render_3d_view_textured(t_data *data, t_texture *tex,
					int x_offset);

// texture_raycast.c
void			normalize_ray_angle(float *ray_angle);
void			init_texture_raycast(t_data *data, t_raycast *vars,
					float ray_angle);
void			setup_texture_step_dist(t_raycast *vars,
					t_ray_result *result, t_data *data);
void			execute_texture_dda(t_raycast *vars,
					t_ray_result *result, t_data *data);
void			set_wall_distance(t_raycast *vars,
					t_ray_result *result, t_data *data);

// texture_render.c
void			init_texture_wall_vars(t_texture_wall_vars *vars,
					t_ray_result ray_result, t_data *data, t_texture *tex);
void			render_texture_wall_pixels(t_texture_wall_vars *vars,
					t_wall_pixel_params *params);

// wall_render.c
void			draw_ceiling(t_data *data, t_wall *wall);
void			draw_floor(t_data *data, t_wall *wall);
void			draw_textured_wall(t_data *data, t_wall *wall);

// window.c
int				key_hook(int keycode, t_data *data);
int				close_hook(t_data *data);
void			update_player_state(t_data *data, float new_x, float new_y,
					float new_angle);

// window_utils.c
void			init_mlx(t_data *data);
void			init_textures(t_data *data);
void			render_complete_view(t_data *data);
void			resize_window(t_data *data);

// render.c
void			draw_separator(t_data *data);

#endif