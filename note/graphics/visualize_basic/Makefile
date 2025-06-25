NAME = mlx_basic
SRC = init.c main.c player.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
CC = gcc
CFLAG = -Wall -Wextra -Werror 
MLX_PATH = ../../../minilibx
INCLUDES = -I$(MLX_PATH)
LIBS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

all: $(NAME)

circle: CFLAG += -DCIRCLE
circle: all

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) $(LIBS) -o $(OBJ_DIR)/$@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAG) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(OBJ_DIR)/$(NAME)

re: fclean all

.PHONY : all clean fclean re