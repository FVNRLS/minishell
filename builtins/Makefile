NAME = cmd.a

SRC =	pwd.c \
		bin_utils.c \
		env.c \
		cd.c \
		echo.c \
		export.c \
		unset.c \
		exit.c \
		
MAIN = main_tests.c

OBJS = $(SRC:.c=.o)

CC = @gcc

AR = ar -r 

C_FLAGS = -Wall -Wextra #-Werror

$(NAME): $(OBJS)
	rm -f *.o
	$(CC) $(C_FLAGS) $(SRC) $(MAIN) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f *.out

re: fclean all

