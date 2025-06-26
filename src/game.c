/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:10:40 by albbermu          #+#    #+#             */
/*   Updated: 2025/06/26 16:11:58 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_complete_view(t_data *data)
{
    // Clear both views
    clear_2d_view(data);
    clear_3d_view(data);
    
    // Render 2D view (left half)
    draw_map_2d(data);
    draw_rays_2d(data);
    draw_player_2d(data);
    
    // Draw separator
    draw_separator(data);
    
    // Render 3D view (right half)
    render_3d_view(data);
    
    // Update display
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int key_hook(int keycode, t_data *data)
{
    int move_speed = 5;
    float rotation_speed = 0.1;
    
    float new_x = data->player_x;
    float new_y = data->player_y;
    float new_angle = data->player_angle;
    
    // Movement controls
    if (keycode == 'w' || keycode == 'W') {
        new_x += data->player_dx * move_speed;
        new_y += data->player_dy * move_speed;
    }
    if (keycode == 's' || keycode == 'S') {
        new_x -= data->player_dx * move_speed;
        new_y -= data->player_dy * move_speed;
    }
    if (keycode == 'a' || keycode == 'A') {
        new_angle += rotation_speed;
    }
    if (keycode == 'd' || keycode == 'D') {
        new_angle -= rotation_speed;
    }
    
    // View mode switching
    if (keycode == ' ') { // Spacebar to switch views
        data->view_mode = (data->view_mode + 1) % 3;
    }
    
    // Collision detection
    if (!is_wall((int)new_x, (int)new_y) && 
        new_x >= 10 && new_x < MAP_WIDTH-10 && new_y >= 10 && new_y < HEIGHT-10) {
        data->player_x = new_x;
        data->player_y = new_y;
    }
    
    // Update angle and direction
    data->player_angle = new_angle;
    data->player_dx = cos(data->player_angle);
    data->player_dy = sin(data->player_angle);
    
    // Render based on view mode
    render_complete_view(data);
    
    return (0);
}
