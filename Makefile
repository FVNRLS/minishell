# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 15:37:00 by rmazurit          #+#    #+#              #
#    Updated: 2022/09/08 16:41:16 by rmazurit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell

CC 			= 	cc

RM 			= 	rm -f

FLAGS 		= 	-Wall -Wextra -Werror -g

SRC 		= 	main.c 								\
				src/initializer/main_init.c			\
				src/initializer/envp_init.c			\
				src/initializer/builtins_init.c		\
				src/destructor.c					\
				builtins/env.c						\
				src/history_tracker.c				\

TOOLS_SRC	= 	src/tools/ft_calloc.c				\
				src/tools/ft_bzero.c				\
				src/tools/ft_new_node.c				\
				src/tools/ft_add_back.c				\
				src/tools/ft_add_front.c			\
				src/tools/ft_lstclear.c				\
				src/tools/ft_lstsize.c				\
				src/tools/ft_strdup.c				\
				src/tools/ft_strlen.c				\


OBJ 		= 	${SRC:.c=.o}
TOOLS_OBJ 	=	${TOOLS_SRC:.c=.o}

INCREADH 	=	-I /Users/$(USER)/.brew/opt/readline/include
INCREADL 	=	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib

.c.o:
	${CC} ${FLAGS} ${INCREADH} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ) $(TOOLS_OBJ)
	${CC} ${FLAGS} ${OBJ} ${TOOLS_OBJ} ${INCREADL} -o ${NAME}

all: $(NAME)

clean:
	rm -f ${OBJ} ${TOOLS_OBJ}

fclean:
	rm -f ${OBJ} ${TOOLS_OBJ} ${NAME}

re: fclean all

.PHONY: all clean fclean re