EXEC		= fractal
SRC_PATH	= srcs
SRC_NAME	= main.c\
		  error_management.c\
		  color_management.c\
		  mandelbrot.c
SRC		= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ_PATH	= objs
OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ		= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
DEPS_PATH	= includes
INCLUDE		= $(addprefix -I,$(DEPS_PATH))
MLXFLAGS	= -lm -lmlx -lX11 -lXext -lpthread
FLAGS		= -Werror -Wextra -Wall -std=c99 -g -D_REENTRANT -O3
CFLAGS		= $(FLAGS) $(MLXFLAGS)
LDFLAGS		=
CC		= gcc

all: $(OBJ_PATH) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_PATH):
	mkdir $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

clean:
	rm -fv $(OBJ)
	rm -rfv $(OBJ_PATH)
	rm -fv $(EXEC)

re: clean all

.PHONY: clean re
