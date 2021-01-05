# NAME = cub3D
# SRC_DIR = src/
# OBJ_DIR = obj/
# MLX_DIR = minilibx_opengl/
# INCLUDES = -I ./includes -I ./
# CC = gcc
# FLAGS = -Wall -Wextra -Werror
# MLX_FLAGS = -g -L $(MLX_DIR) -lmlx -framework OpenGL -framework Appkit -lm
# LIBFT = libft.a
# SRCS =	cub3d.c \
# 		ft_utils.c \
# 		frame_loop.c

# SRC = $(addprefix $(SRC_DIR), $(SRCS))
# OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# all: $(NAME)

# $(NAME):$(OBJ)
# 	@make -C $(MLX_DIR)
# 	@cp	$(MLX_DIR)libmlx.a ./
# 	$(CC) libmlx.a $(INCLUDES) $(OBJ) $(MLX_FLAGS) -o $(NAME)

# $(OBJ_DIR)%.o : $(SRC_DIR)%.c
# 	@$(CC) $(FLAGS) $(INCLUDES) -I $(MLX_DIR) -c $< -o $@

# clean:
# 	@rm -rf $(OBJ)
# 	@rm -f *.bmp

# fclean: clean
# 	@rm -f $(NAME)
# 	@rm -f libmlx.a

# re: fclean all

# .PHONY: all clean fclean re




NAME = cub3D
SRCS = ./src/
# FUNC =	cub3d \
		ft_utils \
		get_next_line \
		get_next_line_utils \
		frame_loop \

FUNC =	parser \
		get_next_line \
		get_next_line_utils \
		ft_split_whitespaces
		
SRC = $(addprefix $(SRCS), $(addsuffix .c, $(FUNC)))
OBJ = $(addprefix $(SRCS), $(addsuffix .o, $(FUNC)))
FLAGS = -g -Wall -Werror -Wextra
all: $(NAME)
$(NAME): $(OBJ)
	$(MAKE) -C ./libft/
	$(MAKE) bonus -C ./libft/
	$(MAKE) -C ./minilibx_opengl
	cp ./minilibx_opengl/libmlx.a .
	cp ./libft/libft.a .
	# gcc -g -I. ./libft.a -L ./minilibx_opengl -lmlx -framework OpenGL -framework AppKit -lm $(OBJ) -o $(NAME)
	gcc libft.a libmlx.a -I ./includes -I ./libft -L ./ -lmlx -framework OpenGL -framework AppKit -lm $(OBJ) -o $(NAME)
%.o: %.c
	# gcc -o $@ -c $<
	gcc $(FLAGS) -I ./includes -I ./libft -I ./minilibx_opengl -c $< -o $@
clean:
	$(MAKE) clean -C ./libft/
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME) libft.a libmlx.a
re: fclean all
.PHONY: all clean fclean re