NAME = cub3D
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT_DIR = libft/
MLX_DIR = minilibx_opengl/
MLX_MMS = minilibx_mms/
INCLUDES = -I ./includes -I ./libft
FLAGS = -g -Wall -Wextra -Werror
MLX_FLAGS = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit libmlx.a
MLX_FLAGS_MMS = -L $(MLX_MMS) -lmlx -framework OpenGL -framework AppKit libmlx.dylib
LIBFT = libft.a
SRCS = cub3d.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_split_whitespaces.c \
		clear.c \
		get_resolution.c \
		get_color.c \
		get_path.c \
		get_map.c \
		make_square.c \
		color_utils.c \
		utils.c \
		sprite_utils.c \
		frame_loop.c \
		raycasting.c \
		drawing.c \
		sprites.c \
		keys.c \
		parser.c \
		save_bmp.c
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
all: $(NAME)
$(NAME): $(OBJ)
	@make -C $(MLX_DIR)
	@make -C $(MLX_MMS)
	@make -C $(LIBFT_DIR) bonus
	@make -C $(LIBFT_DIR)
	@cp $(MLX_DIR)libmlx.a ./
	@cp $(MLX_MMS)libmlx.dylib ./
	@cp $(LIBFT_DIR)libft.a ./
	gcc $(INCLUDES) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(MLX_FLAGS_MMS) -o $(NAME)
$(OBJ): $(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -I $(MLX_DIR) -I $(MLX_MMS) -c $< -o $@
clean:
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@rm -f *.bmp
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -f libft.a
	@rm -f libmlx.a
	@rm -f libmlx.dylib
re: fclean all

.PHONY: all clean fclean re