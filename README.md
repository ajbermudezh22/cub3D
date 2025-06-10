 # cub3D

## The Project
- to create a 3D graphical representation of the inside of a maze
- from a first-person perspective
- by using ray-casting principles

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

compile the program:
```
make
```

run the program:
```
./cub3D map.cub
```


