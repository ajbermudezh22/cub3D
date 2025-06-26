#ifndef RAYCAST_H
# define RAYCAST_H

#include "main.h"

// Function prototypes
float	cast_ray_2d(t_data *data, float ray_angle, int *hit_x, int *hit_y);
void	draw_rays_2d(t_data *data);
void	draw_player_2d(t_data *data);

#endif
