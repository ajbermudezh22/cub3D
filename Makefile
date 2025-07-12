# ──────────────────────────────────────────────────────────────────────────────
#                                  cub3d Makefile
# ──────────────────────────────────────────────────────────────────────────────

NAME      := cub3D
CC        := cc
CFLAGS    := -Wall -Wextra -Werror -g \
             -I./includes \
             -I./libft \
             -I./$(MLX_PATH)

# MiniLibX (adjust if your folder is named differently)
MLX_PATH  := minilibx
MLX_FLAGS := -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

# Your libft static archive
LIBFT     := libft/libft.a

# Source files (at project root)
SRC_DIR	  := src
SRCS_LIST := main.c \
			 draw.c \
             map.c \
			 parser.c \
			 parser_content.c \
			 parser_map.c \
			 parser_utils.c \
			 parser_utils2.c \
             raycast.c \
			 raycast_utils2.c \
			 render.c \
			 texture.c \
			 texture_utils.c \
			 texture_raycast.c \
			 texture_render.c \
			 utils.c \
			 wall_render.c \
             window.c \
			 window_utils.c
SRCS      := $(addprefix $(SRC_DIR)/, $(SRCS_LIST))

# Build objs into a parallel directory tree under objs/
OBJDIR    := objs
OBJS      := $(patsubst $(SRC_DIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# All your project headers
HDRS      := includes/cub3d.h

# ──────────────────────────────────────────────────────────────────────────────
#  Targets
# ──────────────────────────────────────────────────────────────────────────────

all: $(NAME)

# Link: build libft first, then link everything
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Build libft if needed
$(LIBFT):
	@$(MAKE) -C libft

# Compile each .c from src/ into objs/
$(OBJDIR)/%.o: $(SRC_DIR)/%.c $(HDRS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Remove just your object tree and libft's objects
clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C libft

# Full clean including the executable
fclean: clean
	@rm -f $(NAME)

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re