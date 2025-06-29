NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Detect OS
UNAME_S := $(shell uname -s)

# MLX configuration based on OS
ifeq ($(UNAME_S),Linux)
	MLX_PATH = ./minilibx-linux
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
	MLX_INCLUDES = -I$(MLX_PATH)
else ifeq ($(UNAME_S),Darwin)
	MLX_PATH = ./minilibx
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
	MLX_INCLUDES = -I$(MLX_PATH)
else
	# Default to Linux
	MLX_PATH = ./minilibx-linux
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
	MLX_INCLUDES = -I$(MLX_PATH)
endif

SOURCES = main.c main_utils.c render3d.c texture.c parser.c map.c map_utils.c map_render.c window.c window_init.c window_events.c window_helpers.c raycast.c raycast_draw.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c main.h texture.h parser.h map.h window.h raycast.h
	$(CC) $(CFLAGS) $(MLX_INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re