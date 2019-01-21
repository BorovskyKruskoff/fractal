EXEC		= fractal
SRC_PATH	= srcs
SRC_NAME	= main.c\
		  error_management.c
SRC		= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ_PATH	= objs
OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ		= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
DEPS_PATH	= includes
INCLUDE		= $(addprefix -I,$(DEPS_PATH))
MLXFLAGS	= -lm -lmlx -lX11 -lXext
FLAGS		= -Wextra -Wall -std=c99
CFLAGS		= $(FLAGS) $(MLXFLAGS)
LDFLAGS		=
CC		= gcc

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -fv $(OBJ)
	rm -fv $(NAME)

re: fclean all

.PHONY: clean re
