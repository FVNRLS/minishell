cmake_minimum_required(VERSION 3.22)
project(minishell C)

set(CMAKE_C_STANDARD 99)


add_executable(minishell main.c

        #INITIALIZER/DESTRUCTOR:
        src/initializer/main_init.c
        src/initializer/envp_init.c
        src/initializer/builtins_init.c
        src/destructor.c

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

        #BUILTINS:
        builtins/env.c

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
        src/parser/token_merger.c
        src/parser/checker.c

        #MESSAGE PRINTER
        src/message_printer.c
        src/parser/parser.c src/parser/redirecter.c)

target_link_libraries(minishell edit)

