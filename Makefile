# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 15:37:00 by rmazurit          #+#    #+#              #
#    Updated: 2022/10/04 15:09:36 by jjesberg         ###   ########.fr        #
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
				src/initializer/fd_init.c 			\
				src/initializer/data_containers_init.c \
				src/destructor.c					\
				src/builtins/env.c					\
				src/builtins/cd.c					\
				src/builtins/echo.c					\
				src/builtins/mini_exit.c			\
				src/builtins/export.c				\
				src/builtins/export_utils.c			\
				src/builtins/pwd.c					\
				src/builtins/unset.c				\
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
				src/parser/parser.c					\
				src/parser/parsing_checker.c		\
				src/parser/redirecter/redirecter.c	\
				src/parser/redirecter/fd_closer.c	\
                src/parser/redirecter/heredoc_creater.c	\
                src/parser/redirecter/fd_opener.c	\
				src/executer/executer.c				\
				src/executer/cmd_extractor.c 		\
		        src/pipex/pipe_processor.c			\
		        src/pipex/cmd_exec_redirecter.c		\
				src/signals/signals.c				\

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
				src/tools/ft_atoi.c					\
				src/tools/ft_split.c				\
				src/tools/ft_strjoin.c				\
				src/tools/ft_haschar.c				\
				src/tools/ft_get_builtin.c			\
				src/tools/ft_cleansplit.c			\
				src/tools/ft_print_list.c			\
				src/tools/ft_strncmp.c				\
				src/tools/ft_splitlen.c				\
				src/tools/ft_isnumber.c				\
				src/tools/ft_isdigit.c				\
				src/tools/ft_getenvp.c				\
				src/tools/ft_isprint.c				\
        		src/tools/ft_del_first_token.c		\
				src/tools/ft_get_num_cmds.c			\
				src/tools/ft_isalpha.c				\
				src/tools/ft_check_plus.c			\

OBJ 		= 	${SRC:.c=.o}
TOOLS_OBJ 	=	${TOOLS_SRC:.c=.o}

INCREADH 	=	-I /Users/$(USER)/.brew/opt/readline/include
INCREADL 	=	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib

.c.o:
	${CC} ${FLAGS} ${INCREADH} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ) $(TOOLS_OBJ)
	${CC} ${FLAGS} ${OBJ} ${TOOLS_OBJ} ${INCREADL} -o ${NAME}
	rm -rf ./builtins/*.o

all: $(NAME)

clean:
	rm -f ${OBJ} ${TOOLS_OBJ}

fclean:
	rm -f ${OBJ} ${TOOLS_OBJ} ${NAME}

re: fclean all

.PHONY: all clean fclean re