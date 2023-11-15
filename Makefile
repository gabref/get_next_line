NAME 	= bin/final
SRC 	= $(wildcard src/*.c)
OBJ 	= $(patsubst src/%.c, obj/%.o, $(SRC))
CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g3

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
