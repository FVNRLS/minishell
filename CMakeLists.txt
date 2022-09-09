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
        src/tools/ft_add_back.c
        src/tools/ft_add_front.c
        src/tools/ft_lstclear.c
        src/tools/ft_lstsize.c
        src/tools/ft_strdup.c
        src/tools/ft_strlen.c
        src/tools/ft_strcmp.c
        src/tools/ft_join_char.c

        #BUILTINS:
        builtins/env.c

        #HISTORY
        src/history_tracker.c

        #LEXER
        src/lexer/lexer.c
   )

target_link_libraries(minishell edit)

