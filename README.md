# cub3D

## The Project
This Project aims to create a dynamic 3d maze which is displayed from a first-person perspective. The ray-casting principles are implemented.

## Project Requirements
- Smooth Management of the window
	- [] changing to another window
	- [] minimizing window
	- [] etc
- Rules of displaying the window
	- [] The arrow keys(Left, Right): look left and right
	- [] W, A, S, and D keys: move the point of view
	- [] ESC: closes the window and exit 
	- [] the cross on the window: closes the window and exit
- Validate the textures, colors, and map (*.cub)
	- [] Part 1: W/A/S/D textures (four different textures)
	- [] Part 2: F/C colors (two different colors)
	- [] Part 3: Actual map composed of 6 characters
		: 0 = an empty space
		: 1 = a wall
		: N,S,E,W = the player's start position and spawning orientation
		- [] if the map is not closed/surrounded by walls, the program must return an error
		- [] can have spaces between the walls
	- [] Between Part 1-3: can have empty lines, spaces, except for the map itself
	- [] Any misconfiguaration in the file: return `Error/n <MESSAGE>` and exit
	
## Recommended
- to use images of minilibx

## How to Use

Compile the program:
```
make
```

Run the program:
```
./cub3D <PATH_TO_MAP.cub>
```
The program takes a map file as an argument. Maps are contained in the `maps` directory.

## How to Control with Keyboard

- **W**: move forward
- **S**: move backward
- **A**: strafe left
- **D**: strafe right
- **←**: left arrow: rotate left
- **→**: rotate right

## How to Clone
Clone the repository including the MiniLibX submodule:
```
git clone --recursive https://github.com/ajbermudezh22/cub3D.git
```
Or:
```
git clone https://github.com/ajbermudezh22/cub3D.git
git submodule update --init --recursive
```

## References
- 