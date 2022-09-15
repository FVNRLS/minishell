NAME = cmd.a

SRC =	pwd.c \
		bin_utils.c \
		env.c \
		cd.c \
		echo.c \
		export.c \
		unset.c \
		mini_exit.c \
		
MAIN = main_tests.c

OBJS = $(SRC:.c=.o)

CC = gcc

AR = ar -r 

C_FLAGS = -Wall -Wextra #-Werror

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(SRC) $(MAIN) -o $(NAME)
	rm -f *.o
	./cmd.a

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f *.out

re: fclean all

