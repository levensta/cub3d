# NAME = cub3D

# AR = ar rc

# CC = gcc

# CUB = -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit

# FLAGS = -Wall -Wextra -Werror -g

# MLX_DIR = ./minilibx_mms/
# MLX_FLAGS = -L $(MLX_DIR) -lmlx -framework OpenGL -framework Appkit

# HEADER = -I ./includes 

# SOURCE = 	cub3d.c \
# 			ft_utils.c

# OBJECT = $(SOURCE:.c=.o)

# all: minilib $(NAME)

# minilib:
# 	$(MAKE) -C $(MLX_DIR)
# 	cp $(MLX_DIR)libmlx.dylib ./

# %.o: %.c
# 	$(CC) $(FLAGS) $(INCLUDES) -I $(MLX_DIR) -c $< -o $@

# $(NAME): $(OBJECT)
# 	$(CC) $(FLAGS) $(OBJECT) $(INCLUDES) $(MLX_FLAGS) -I $(MLX_DIR) -o $@

# clean:
# 	rm -f $(OBJECT)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all bonus clean fclean re

NAME = cub3D
SRC_DIR = src/
OBJ_DIR = obj/
MLX_DIR = minilibx_mms/
INCLUDES = -I ./includes -I ./
CC = gcc
FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L $(MLX_DIR) -lmlx -framework OpenGL -framework Appkit
LIBFT = libft.a
SRCS =	cub3d.c \
		ft_utils.c

SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME):$(OBJ)
	@make -C $(MLX_DIR)
	@cp	$(MLX_DIR)libmlx.dylib ./
	$(CC) $(INCLUDES) $(OBJ) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(FLAGS) $(INCLUDES) -I $(MLX_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@rm -f *.bmp

fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.dylib

re: fclean all

.PHONY: all clean fclean run re