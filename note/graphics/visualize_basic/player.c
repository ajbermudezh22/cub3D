#include "main.h"
/* note

	this program allows user to move the player by pressing `w`

*/


int key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == KEY_W || keycode == KEY_UP)
	{
		data->player->y -= data->player->size;	//!: moving up decreases `y-axis`
		if (data->player->y < 0)			//!: set to MIN  if(- after decrease) 
			data->player->y = 0;
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		data->player->y += data->player->size;
		if (data->player->y > HEIGHT)
			data->player->y = HEIGHT;			//!: set to HEIGHT(MAX) if(out LIMIT after increase)
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		data->player->x -= data->player->size;
		if (data->player->x < 0)
			data->player->x = 0;
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		data->player->x += data->player->size;
		if (data->player->x > WIDTH)
			data->player->x = WIDTH;
	}
	update_display(data);
	return 0;
}

void	draw_player(t_data *data)
{
	//loop through a square area around player center
	int radius = data->player->size / 2;
	int x = data->player->x - radius;
	int y = data->player->y - radius;

	while (y <= data->player->y + radius)
	{
		x = data->player->x - radius; 
		while (x <= data->player->x + radius)
		{
#ifdef CIRCLE
			//ver1:  circle equation: (x-h)² + (y-k)² ≤ r²
			if ((x - data->player->x) * (x - data->player->x) + (y - data->player->y) * (y - data->player->y) <= radius * radius &&
				x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				data->addr[y * (data->line_len / 4) + x] = 0x00FFFF00; // Yellow
#else
			//ver2 : square
			if ( x <= data->player->x + radius && y <= data->player->y + radius && x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT )
				data->addr[y * (data->line_len / 4) + x] = 0x00FFFF00; // Yellow
#endif
			x++;
		}
		y++;
	}
}
