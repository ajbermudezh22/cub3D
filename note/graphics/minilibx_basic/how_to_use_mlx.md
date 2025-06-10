# how to use mlx

### link against mlx
- If the program is not linked against MiniLibX library, it can't be compiled.

### how to link?
- include <mlx.h> header
- add the linker flags in `Makefile`

```Makefile
Name = mlx_basic
# rest of the code

MLX_PATH = ../../minilibx
INCLUDES = -I$(MLX_PATH)
LIBS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# rest of the code
```

Key concepts:
1. `MLX_PATH`: points to MIniLibX dir
2. `INCLUDES` : include the paths
3. `LIBS`: necessary libraries
	- `-lmx`: minilibx lib
	- `-lXext` and `-lX11`: X11 lib required by minilibx
	- `-lm`: math lib