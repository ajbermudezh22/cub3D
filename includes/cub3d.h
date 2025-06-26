/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:43:07 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/26 16:34:27 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <stddef.h> //size_t
# include <stdlib.h> // exit() - free()
# include <unistd.h> // write() - close()
# include <stdbool.h> //bool
# include <fcntl.h> //open() - close()
# include <string.h>
# include <errno.h> //strerror
# include <signal.h> //signal
# include <termios.h>
# include <limits.h> //INT_MAX
#include <math.h>

#define WIDTH      1000
#define HEIGHT     500
#define MAP_WIDTH  500
#define VIEW_WIDTH 500

#define PI         3.141592f
#define DR         (PI/180.0f)

#define mapX       8
#define mapY       8
#define mapS       64
extern int map[mapX * mapY];

#define FOV        60
#define NUM_RAYS   500
#define WALL_HEIGHT 200

#define KEY_ESC    65307

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    int     *addr;
    int     bits_per_pixel;
    int     line_len;
    int     endian;
    int     player_x;
    int     player_y;
    float   player_angle;
    float   player_dx;
    float   player_dy;
    int     view_mode;
}   t_data;

// pixel.c
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
int     blend_colors(int c1, int c2, float alpha);

// init.c
void    init(t_data *data);

// 2D draw
void    clear_2d_view(t_data *data);
void    draw_map_2d(t_data *data);
void    draw_rays_2d(t_data *data);
void    draw_player_2d(t_data *data);
void    draw_separator(t_data *data);

// map.c
int is_wall(int x, int y);

// ray2d.c
float   cast_ray_2d(t_data *data, float ang, int *hit_x, int *hit_y);

// render3d.c
float   cast_ray_3d(t_data *data, float ang);
void    draw_wall_slice(t_data *data, int x, float dist, int wall_color);
void    render_3d_view(t_data *data);
void    clear_3d_view(t_data *data);

// game.c
void    render_complete_view(t_data *data);
int     key_hook(int keycode, t_data *data);

#endif
