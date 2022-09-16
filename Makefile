# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 15:37:00 by rmazurit          #+#    #+#              #
#    Updated: 2022/09/16 11:05:03 by jjesberg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell

CC 			= 	cc

RM 			= 	rm -f

FLAGS 		= 	-Wall -Wextra -Werror

SRC 		= 	main.c 								\
				src/initializer/main_init.c			\
				src/initializer/envp_init.c			\
				src/initializer/builtins_init.c		\
				src/destructor.c					\
				builtins/env.c						\
				builtins/cd.c						\
				builtins/bin_utils.c				\
				builtins/echo.c						\
				builtins/mini_exit.c				\
				builtins/export.c					\
				builtins/pwd.c						\
				builtins/unset.c					\
				src/history_tracker.c				\
				src/lexer/lexer.c					\
				src/lexer/tokenizer.c				\
				src/lexer/single_quotes_handler.c	\
				src/lexer/redirections_handler.c	\
				src/lexer/double_quotes_handler.c	\
				src/message_printer.c				\
				src/lexer/words_handler.c			\
				src/lexer/expander/expansion_handler.c \
				src/lexer/expander/expansion_rules.c	\
				src/parser/token_merger.c			\
				src/parser/checker.c				\

TOOLS_SRC	=	src/tools/ft_calloc.c				\
				src/tools/ft_bzero.c				\
				src/tools/ft_new_envp.c				\
				src/tools/ft_new_token.c			\
				src/tools/ft_add_envp_back.c		\
				src/tools/ft_lstclear.c				\
				src/tools/ft_lstsize.c				\
				src/tools/ft_strdup.c				\
				src/tools/ft_strlen.c				\
				src/tools/ft_strcmp.c				\
				src/tools/ft_join_char.c			\
				src/tools/ft_strtrim.c				\
				src/tools/ft_add_token_back.c		\
				src/tools/ft_itoa.c					\
				src/tools/ft_split.c				\
				src/tools/ft_strjoin.c				\


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