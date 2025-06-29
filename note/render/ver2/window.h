#ifndef WINDOW_H
# define WINDOW_H

#include "basic1.h"

// Function prototypes
void	init_mlx(t_data *data);
void	init_textures(t_data *data);
void	render_complete_view(t_data *data);
void	draw_separator(t_data *data);
int		key_hook(int keycode, t_data *data);

#endif
