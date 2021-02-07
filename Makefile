NAME = cub3D
SRCS = ./src/

FUNC =	cub3d \
		get_next_line \
		get_next_line_utils \
		ft_split_whitespaces \
		clear \
		error \
		get_resolution \
		get_color \
		get_path \
		get_map \
		make_square \
		color_utils \
		image_utils \
		sprite_utils \
		frame_loop \
		drawing \
		keys \
		parser \
		save_bmp
		
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
	gcc libft.a libmlx.a -I ./includes -I ./libft -L ./ -lmlx -framework OpenGL -framework AppKit -lm $(OBJ) -o $(NAME)
	mv $(OBJ) ./obj
%.o: %.c
	gcc $(FLAGS) -I ./includes -I ./libft -I ./minilibx_opengl -c $< -o $@
clean:
	$(MAKE) clean -C ./libft/
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME) libft.a libmlx.a
re: fclean all
.PHONY: all clean fclean re