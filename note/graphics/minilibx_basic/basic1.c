#include "basic1.h"

// int key_press(int keycode, t_data *data)
// {
// 	if (keycode == ESC)

// 	else if (keycode == LEFT_)

// }

/* notes
[code]
part3: open window
part4: this return code never reachable
	why? mlx_loop doesn't return

[functions]
1.mlx_new_window()
	- creates empty image buffer in memory with speicifed dimension(WIDTH*HEIGHT)

2.mlx_loop
	- create the event to keep window open

3.mlx_get_data_addr()
	- provides direct access to the mem that stores image data
	- allows you to modify pixels
	- the param's value doesn't have to be assigned
		- why? the functions outputs the values
			- &bits_per_pixel: the number of bits in one pixel (typically 32 for true color format - 8 bits each for RGBA)
			- &line_len:  the number of bytes in one line of the image. This is important because image data is stored linearly in memory, and this value helps you calculate the correct position of a pixel.
			- &endian: the endian value (little endian = 0, big endian = 1). 

4. mlx_put_image_to_window()
	- copy contents of the image buffer to the window
	- without this, your drawing exist in memory but never appear on window
	- Think: image buffer = a canvas, this function = hanging the canvas on the wall

*/

//init MLX && create window && prep for rendering
void	init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D_window");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_len, &data->endian);
}

//on x button
int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int main()
{
	t_data	data;

	//part1
	init(&data);

	// part2: Draw something (red square) to the image buffer
	for(int y = 100; y < 200; y++) {
		for(int x = 100; x < 200; x++) {
			data.addr[y * (data.line_len / 4) + x] = 0x00FF0000; // Red color
		}
	}

		// to display the image from part2
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	//part3
	mlx_hook(data.win, 17, 0, close_window, &data); // setup even hook: Window close 
	mlx_loop(data.mlx);

	//part4
	return (0); 
}