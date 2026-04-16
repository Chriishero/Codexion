CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

NAME = codexion
SRC = coders/main.c coders/parser.c coders/codexion.c \
	  coders/monitor.c coders/init.c coders/init2.c \
	  coders/queue.c coders/coder.c coders/dongle.c \
	  coders/logs.c coders/utils.c coders/free_data.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all