#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "texture.h"

// Map configuration structure
typedef struct s_config
{
    char    *north_texture_path;
    char    *south_texture_path;
    char    *west_texture_path;
    char    *east_texture_path;
    int     floor_r;
    int     floor_g;
    int     floor_b;
    int     ceiling_r;
    int     ceiling_g;
    int     ceiling_b;
    char    **map_grid;
    int     map_width;
    int     map_height;
    int     player_x;
    int     player_y;
    char    player_dir;
} t_config;

// Function prototypes
int     parse_cub_file(char *filename, t_config *config);
void    free_config(t_config *config);
int     parse_color(char *line, int *r, int *g, int *b);
int parse_texture_path(char *line, char **path, char *cub_file_dir);
int     validate_map(t_config *config);
void    find_player_position(t_config *config);

#endif
