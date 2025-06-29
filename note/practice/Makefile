# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 14:00:04 by albbermu          #+#    #+#              #
#    Updated: 2025/06/04 14:21:19 by albbermu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       := cc
CFLAGS   := -Wall -Wextra -Werror -g

NAME      = cub3D
HEADER    = includes/cub3d.h

LIBFT_PATH    := libft
LIBFT_ARCHIVE := $(LIBFT_PATH)/libft.a

MLX_PATH      := minilibx
MLX_ARCHIVE   := $(MLX_PATH)/libmlx.a
MLX_FLAGS     := -L$(MLX_PATH) -lmlx -L/usr/X11/lib -lXext -lX11 -lm -lbsd

SRC := \
	src/main.c \
	# src/init.c \
	# src/raycast.c \
	# src/draw.c \
	# src/texture.c \
	# src/hooks.c \
	# src/map.c \
	# src/utils.c

# Color codes for messages
GREEN  := \033[0;32m
YELLOW := \033[0;33m
RESET  := \033[0m

all: $(NAME)

$(NAME): $(SRC) $(LIBFT_ARCHIVE) $(MLX_ARCHIVE) $(HEADER)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $(SRC) \
		-I$(LIBFT_PATH) -I$(MLX_PATH) -Iincludes \
		-L$(LIBFT_PATH) -lft \
		$(MLX_FLAGS)
	@echo "$(GREEN)$(NAME) compiled successfully.$(RESET)"

$(LIBFT_ARCHIVE):
	@echo "$(GREEN)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH)
	@echo "$(GREEN)Libft compiled successfully.$(RESET)"

$(MLX_ARCHIVE):
	@echo "$(GREEN)Building MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_PATH)
	@echo "$(GREEN)MiniLibX compiled successfully.$(RESET)"


clean:
	@echo "$(YELLOW)Cleaning object files in libft and MiniLibX...$(RESET)"
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean
	@echo "$(YELLOW)Removed library object files.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing $(NAME) binary and libft.a...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@echo "$(YELLOW)All cleaned.$(RESET)"

re: fclean all

valgrind: $(NAME)
	@echo "$(YELLOW)Running $(NAME) under Valgrind...$(RESET)"
	valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         ./$(NAME)

memcheck: $(NAME)
	@echo "$(YELLOW)Running $(NAME) under Valgrind (log → valgrind_output.txt)...$(RESET)"
	valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         --log-file=valgrind_output.txt \
	         ./$(NAME)

.PHONY: all clean fclean re valgrind memcheck
