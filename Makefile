NAME 	= bin/final
# SRC 	= $(wildcard src/*.c)
SRC 	= src/get_next_line.c src/get_next_line_utils.c src/main.c
OBJ 	= $(patsubst src/%.c, obj/%.o, $(SRC))
CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g3 -ggdb

obj/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I src

$(NAME): $(OBJ)
	$(CC) -o $@ $?

all: $(NAME)

run: all
	./$(NAME) < test_file

clean:
	rm -f obj/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
