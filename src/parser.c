/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:19 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/27 14:03:23 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_config(t_config *config)
{
    config->north_texture_path = NULL;
    config->south_texture_path = NULL;
    config->west_texture_path = NULL;
    config->east_texture_path = NULL;
    config->floor_r = -1;
    config->floor_g = -1;
    config->floor_b = -1;
    config->ceiling_r = -1;
    config->ceiling_g = -1;
    config->ceiling_b = -1;
    config->map_grid = NULL;
    config->map_width = 0;
    config->map_height = 0;
    config->player_x = -1;
    config->player_y = -1;
    config->player_dir = '\0';
}

// Parse color values from "R,G,B" format
int parse_color(char *line, int *r, int *g, int *b)
{
    char *token;
    char *line_copy = strdup(line);
    
    token = strtok(line_copy, " \t");
    if (!token) {
        free(line_copy);
        return 0;
    }
    token = strtok(NULL, ",");
    if (!token) {
        free(line_copy);
        return 0;
    }
    *r = atoi(token);
    token = strtok(NULL, ",");
    if (!token) {
        free(line_copy);
        return 0;
    }
    *g = atoi(token);
    token = strtok(NULL, " \t\n");
    if (!token) {
        free(line_copy);
        return 0;
    }
    *b = atoi(token);
    free(line_copy);
    if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
        return 0;
    return 1;
}

int parse_texture_path(char *line, char **path, char *cub_file_dir)
{
    char *token;
    char *line_copy = strdup(line);
    
    token = strtok(line_copy, " \t");
    if (!token) {
        free(line_copy);
        return 0;
    }
    token = strtok(NULL, " \t\n");
    if (!token) {
        free(line_copy);
        return 0;
    }
    if (token[0] != '/')
	{
        *path = malloc(strlen(cub_file_dir) + strlen(token) + 2);
        sprintf(*path, "%s/%s", cub_file_dir, token);
    }
	else
		*path = strdup(token);
    free(line_copy);
    return 1;
}

// Find player position and direction in map
void find_player_position(t_config *config)
{
    for (int y = 0; y < config->map_height; y++) {
        for (int x = 0; x < config->map_width; x++) {
            char c = config->map_grid[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                config->player_x = x;
                config->player_y = y;
                config->player_dir = c;
                // Replace player position with empty space in map
                config->map_grid[y][x] = '0';
                return;
            }
        }
    }
}

// Validate that map is surrounded by walls
int validate_map(t_config *config)
{
    if (!config->map_grid || config->map_height == 0 || config->map_width == 0)
        return 0;
    
    // Check if player was found
    if (config->player_x == -1 || config->player_y == -1)
        return 0;
    
    // Check that map is surrounded by walls (simplified check)
    for (int x = 0; x < config->map_width; x++) {
        if (config->map_grid[0][x] != '1' || 
            config->map_grid[config->map_height - 1][x] != '1')
            return 0;
    }
    
    for (int y = 0; y < config->map_height; y++) {
        if (config->map_grid[y][0] != '1' || 
            config->map_grid[y][config->map_width - 1] != '1')
            return 0;
    }
    
    return 1;
}

// Parse .cub file
int parse_cub_file(char *filename, t_config *config)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }
    
    init_config(config);
    
    // Extract directory from filename for relative path resolution
    char *cub_file_dir = malloc(strlen(filename) + 1);
    strcpy(cub_file_dir, filename);
    char *last_slash = strrchr(cub_file_dir, '/');
    if (last_slash) {
        *last_slash = '\0';  // Remove filename, keep directory
    } else {
        strcpy(cub_file_dir, ".");  // Current directory if no slash found
    }
    
    char line[1024];
    int map_started = 0;
    int map_lines = 0;
    char **temp_map = NULL;
    (void) map_started;
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines and comments
        if (line[0] == '\n' || line[0] == '\0')
            continue;
        
        // Parse texture identifiers
        if (strncmp(line, "NO ", 3) == 0) {
            if (!parse_texture_path(line, &config->north_texture_path, cub_file_dir)) {
                printf("Error: Invalid north texture format\n");
                fclose(file);
                free(cub_file_dir);
                return 0;
            }
        }
        else if (strncmp(line, "SO ", 3) == 0) {
            if (!parse_texture_path(line, &config->south_texture_path, cub_file_dir)) {
                printf("Error: Invalid south texture format\n");
                fclose(file);
                free(cub_file_dir);
                return 0;
            }
        }
        else if (strncmp(line, "WE ", 3) == 0) {
            if (!parse_texture_path(line, &config->west_texture_path, cub_file_dir)) {
                printf("Error: Invalid west texture format\n");
                fclose(file);
                free(cub_file_dir);
                return 0;
            }
        }
        else if (strncmp(line, "EA ", 3) == 0) {
            if (!parse_texture_path(line, &config->east_texture_path, cub_file_dir)) {
                printf("Error: Invalid east texture format\n");
                fclose(file);
                free(cub_file_dir);
                return 0;
            }
        }
        // Parse floor color
        else if (strncmp(line, "F ", 2) == 0) {
            if (!parse_color(line, &config->floor_r, &config->floor_g, &config->floor_b)) {
                printf("Error: Invalid floor color format\n");
                fclose(file);
                free(cub_file_dir);
                return 0;
            }
        }
        // Parse ceiling color
        else if (strncmp(line, "C ", 2) == 0) {
            if (!parse_color(line, &config->ceiling_r, &config->ceiling_g, &config->ceiling_b)) {
                printf("Error: Invalid ceiling color format\n");
                fclose(file);
                free(cub_file_dir);
                return 0;
            }
        }
        // Parse map
        else if (line[0] == '1' || line[0] == '0' || strchr(line, 'N') || strchr(line, 'S') || 
                strchr(line, 'E') || strchr(line, 'W')) {
            map_started = 1;
            
            // Remove newline
            int len = strlen(line);
            if (len > 0 && line[len - 1] == '\n')
                line[len - 1] = '\0';
            
            // Reallocate temp_map
            temp_map = realloc(temp_map, sizeof(char*) * (map_lines + 1));
            temp_map[map_lines] = strdup(line);
            
            // Update max width
            if ((int)strlen(line) > config->map_width)
                config->map_width = strlen(line);
            
            map_lines++;
        }
    }
    
    fclose(file);
    free(cub_file_dir);
    
    // Check if all required elements are present
    if (!config->north_texture_path || !config->south_texture_path || 
        !config->west_texture_path || !config->east_texture_path) {
        printf("Error: Missing texture paths\n");
        return 0;
    }
    
    if (config->floor_r == -1 || config->ceiling_r == -1) {
        printf("Error: Missing floor or ceiling colors\n");
        return 0;
    }
    
    if (map_lines == 0) {
        printf("Error: No map found\n");
        return 0;
    }
    
    // Copy map and pad with spaces
    config->map_height = map_lines;
    config->map_grid = malloc(sizeof(char*) * config->map_height);
    
    for (int i = 0; i < map_lines; i++) {
        config->map_grid[i] = malloc(config->map_width + 1);
        strcpy(config->map_grid[i], temp_map[i]);
        
        // Pad with spaces if necessary
        int len = strlen(config->map_grid[i]);
        for (int j = len; j < config->map_width; j++) {
            config->map_grid[i][j] = ' ';
        }
        config->map_grid[i][config->map_width] = '\0';
        
        free(temp_map[i]);
    }
    free(temp_map);
    
    // Find player position
    find_player_position(config);
    
    // Validate map
    if (!validate_map(config)) {
        printf("Error: Invalid map\n");
        return 0;
    }
    
    printf("Parsed .cub file successfully:\n");
    printf("- North texture: %s\n", config->north_texture_path);
    printf("- South texture: %s\n", config->south_texture_path);
    printf("- West texture: %s\n", config->west_texture_path);
    printf("- East texture: %s\n", config->east_texture_path);
    printf("- Floor color: %d,%d,%d\n", config->floor_r, config->floor_g, config->floor_b);
    printf("- Ceiling color: %d,%d,%d\n", config->ceiling_r, config->ceiling_g, config->ceiling_b);
    printf("- Map size: %dx%d\n", config->map_width, config->map_height);
    printf("- Player position: (%d,%d) facing %c\n", config->player_x, config->player_y, config->player_dir);
    
    return 1;
}

// Free config memory
void free_config(t_config *config)
{
    if (config->north_texture_path) free(config->north_texture_path);
    if (config->south_texture_path) free(config->south_texture_path);
    if (config->west_texture_path) free(config->west_texture_path);
    if (config->east_texture_path) free(config->east_texture_path);
    
    if (config->map_grid) {
        for (int i = 0; i < config->map_height; i++) {
            if (config->map_grid[i])
                free(config->map_grid[i]);
        }
        free(config->map_grid);
    }
}
