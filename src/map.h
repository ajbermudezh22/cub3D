#ifndef MAP_H
# define MAP_H

#include "main.h"

// External map variables
extern int mapX, mapY, mapS;
extern int *map;

// Function prototypes
float	get_player_angle(char dir);
void	setup_map_from_config(t_data *data);
void	draw_map_2d(t_data *data);
int		is_wall(int x, int y);

#endif
