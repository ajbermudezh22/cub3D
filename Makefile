# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 14:00:04 by albbermu          #+#    #+#              #
#    Updated: 2025/06/26 16:24:40 by albbermu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME          := cub3D

# Paths
LIBFT_PATH    := libft
MLX_PATH      := minilibx
VPATH         = src

# Archives
LIBFT_ARCHIVE := $(LIBFT_PATH)/libft.a
MLX_ARCHIVE   := $(MLX_PATH)/libmlx.a

# Headers
HEADER        := includes/cub3d.h

# For pretty output
GREEN         := \033[0;32m
YELLOW        := \033[0;33m
RESET         := \033[0m

CC       := cc
CFLAGS   := -Wall -Wextra -Werror -g -Iincludes -I$(LIBFT_PATH) -I$(MLX_PATH)
MLX_FLAGS     := -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
LDFLAGS  := -L$(LIBFT_PATH) -lft $(MLX_FLAGS)

SRC       := main.c init.c pixel.c map.c ray2d.c draw2d.c game.c render3d.c
OBJ       := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_ARCHIVE) $(MLX_ARCHIVE)
	@echo "$(GREEN)Linking $@…$(RESET)"
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(LIBFT_ARCHIVE):
	@$(MAKE) -C $(LIBFT_PATH)

$(MLX_ARCHIVE):
	@$(MAKE) -C $(MLX_PATH)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files…$(RESET)"
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	@echo "$(YELLOW)Removing binary & libft.a…$(RESET)"
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

valgrind: all
	@echo "$(YELLOW)Running under Valgrind…$(RESET)"
	valgrind --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes ./$(NAME)

memcheck: all
	@echo "$(YELLOW)Valgrind log → valgrind_output.txt$(RESET)"
	valgrind --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes \
	         --log-file=valgrind_output.txt ./$(NAME)

.PHONY: all clean fclean re valgrind memcheck
