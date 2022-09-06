NAME = cmd.a

SRC =	pwd.c \
		bin_utils.c \

OBJS = $(SRC:.c=.o)

CC = gcc

AR = ar -r 

C_FLAGS = -c -Wall -Wextra #-Werror

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(SRC)
	$(AR) $(NAME) $(OBJS)
	rm -rf *.o

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all