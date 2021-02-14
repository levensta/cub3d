


MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

CFLAGS=-O3

NAME=libmlx.dylib

INC=-I.
#OPTI=-Ounchecked

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ)
	swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) -lz



%.o: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@

%.swiftmodule: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)

clean:
	rm -f $(NAME) $(OBJ) $(MODULE_OBJ) *.swiftdoc *~

