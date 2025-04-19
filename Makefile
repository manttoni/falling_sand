# Project Name (binary output)
NAME    := pixelator

# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror \
           -Ilib/MLX42/include \
           -Ilib/libft \
		   -g -O3
LDFLAGS := -Llib/MLX42/build -lmlx42 \
           -Llib/libft -lft \
           -ldl -lglfw -pthread -lm

# Directories
SRC_DIR := source
OBJ_DIR := build

# Sources and objects
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(NAME)

# Clone & build MLX42
lib/MLX42/build/libmlx42.a:
	@echo "Cloning MLX42..."
	@mkdir -p lib
	@if [ ! -d lib/MLX42 ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42; \
	fi
	@cmake -S lib/MLX42 -B lib/MLX42/build
	@cmake --build lib/MLX42/build

# Clone & build libft
lib/libft/libft.a:
	@echo "Cloning libft..."
	@mkdir -p lib
	@if [ ! -d lib/libft ]; then \
		git clone https://github.com/manttoni/libft.git lib/libft; \
	fi
	@$(MAKE) -C lib/libft

# Compile source objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | lib/MLX42/build/libmlx42.a lib/libft/libft.a
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link final binary
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Clean object files and executable
clean:
	rm -rf $(OBJ_DIR) $(NAME)
	@$(MAKE) -C lib/libft clean || true
	@rm -rf lib/MLX42/build

# Full clean
fclean: clean
	rm -rf lib/MLX42 lib/libft

# Rebuild all
re: fclean all

.PHONY: all clean fclean re

