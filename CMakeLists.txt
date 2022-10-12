cmake_minimum_required(VERSION 3.22)
project(minishell C)

set(CMAKE_C_STANDARD 99)


add_executable(minishell main.c

        #INITIALIZER/DESTRUCTOR:
        src/initializer/main_init.c
        src/initializer/envp_init.c
        src/initializer/builtins_init.c
        src/destructor.c
        src/initializer/fd_init.c
        src/initializer/data_containers_init.c

        #TOOLS:
        src/tools/ft_calloc.c
        src/tools/ft_bzero.c
        src/tools/ft_new_envp.c
        src/tools/ft_new_token.c
        src/tools/ft_add_envp_back.c
        src/tools/ft_lstclear.c
        src/tools/ft_lstsize.c
        src/tools/ft_strdup.c
        src/tools/ft_strlen.c
        src/tools/ft_strcmp.c
        src/tools/ft_join_char.c
        src/tools/ft_strtrim.c
        src/tools/ft_add_token_back.c
        src/tools/ft_itoa.c
        src/tools/ft_split.c
        src/tools/ft_strjoin.c
        src/tools/ft_cleansplit.c
        src/tools/ft_get_builtin.c
        src/tools/ft_strncmp.c
        src/tools/ft_getenvp.c
        src/tools/ft_isnumber.c
        src/tools/ft_isdigit.c
        src/tools/ft_splitlen.c
        src/tools/ft_haschar.c
        src/tools/ft_isprint.c
        src/tools/ft_del_first_token.c
        src/tools/ft_get_num_cmds.c
        src/tools/ft_isalpha.c
        src/tools/ft_check_plus.c
        src/tools/ft_atoi.c
        src/tools/ft_join_tilde.c

        #HISTORY
        src/history_tracker.c

        #LEXER
        src/lexer/lexer.c
        src/lexer/tokenizer.c
        src/lexer/single_quotes_handler.c
        src/lexer/redirections_handler.c
        src/lexer/double_quotes_handler.c
        src/lexer/words_handler.c
        src/lexer/expander/expansion_handler.c
        src/lexer/expander/expansion_rules.c

        #PARSER
        src/parser/parser.c
        src/parser/parsing_checker.c
        src/parser/token_merger.c
        src/parser/redirecter/redirecter.c
        src/parser/redirecter/fd_closer.c
        src/parser/redirecter/heredoc_creater.c
        src/parser/redirecter/fd_opener.c

        #EXECUTER
        src/executer/cmd_extractor.c
        src/executer/executer.c

        #PIPEX
        src/pipex/pipe_processor.c
        src/pipex/cmd_exec_redirecter.c
        src/pipex/fd_dupper.c

        #BUILTINS
        src/builtins/cd.c
        src/builtins/echo.c
        src/builtins/env.c
        src/builtins/export.c
        src/builtins/export_utils.c
        src/builtins/mini_exit.c
        src/builtins/pwd.c
        src/builtins/unset.c
        src/builtins/cd_utils.c
        src/builtins/change_pwd_utils.c

        #SIGNALS
        src/signals/signals.c

        #MESSAGE PRINTER
        src/message_printer.c
        )

target_link_libraries(minishell edit)

