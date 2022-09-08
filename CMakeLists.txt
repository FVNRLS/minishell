cmake_minimum_required(VERSION 3.22)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell main.c

        #INITIALIZER/DESTRUCTOR:
        src/initializer/main_init.c
        src/initializer/envp_init.c
        src/destructor.c


        #TOOLS:
        src/tools/ft_calloc.c
        src/tools/ft_bzero.c
        src/tools/ft_new_node.c
        src/tools/ft_add_back.c
        src/tools/ft_add_front.c
        src/tools/ft_lstclear.c
        src/tools/ft_lstsize.c

        #PRINTER:
        builtins/env.c
        src/initializer/builtins_init.c
        src/tools/ft_strdup.c
        src/tools/ft_strlen.c incl/builtins.h)
