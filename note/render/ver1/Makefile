NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# MLX flags (adjust path as needed)
MLX_PATH = ./mlx
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

SOURCES = main.c render3d.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c basic1.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re