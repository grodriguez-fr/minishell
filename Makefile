NAME = minishell

SRCS = src/error.c src/exit.c src/funny_graph.c src/main.c src/prompt.c src/parsing/parse_command.c src/parsing/parse_env.c src/parsing/utils/utils_parse_command.c src/parsing/create_env.c src/parsing/file_in_out.c src/builtins/echo.c src/parsing/utils/ft_split_mini.c src/parsing/clean_cmd_redirect.c src/parsing/hear_append.c

OBJS_DIR = obj/

OBJS = $(SRCS:%.c=$(OBJS_DIR)%.zizi)

LIBS = libs/libft/libft.a

HEADER = headers/minishell.h headers/proto.h headers/struct.h

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

CC = cc

all: libft $(NAME) norm funny_graph

$(OBJS_DIR)%.zizi: %.c $(HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf	"\033[1;33m \r\033[2KCreating -c $< -o $\n \033[0m"

libft:
	@make -sC libs/libft

$(NAME): $(LIBS) $(OBJS) $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME)
	@printf	"\033[1;32m \r\033[2KCompiling $(NAME) : DONE \n \033[0m"

norm:
	@norminette | grep 'Error' | echo "\033[1;33m \r\033[2Knorm error \033[0m" || echo "\033[1;32mYou are a genious \033[0m"
	

clean:
	@make clean -sC libs/libft
	@$(RM) $(OBJS)
	@printf	"\033[1;31m \r\033[2KDeleting objects : DONE \033[1;31m\n"

fclean: clean
	@make fclean -sC libs/libft
	@$(RM) $(NAME)
	@printf "\033[1;31m \r\033[2KDeleting executable : DONE \033[1;31m\n\n"

re: fclean all

funny_graph:
	@printf " __  __ _____ _   _ _____  _____ _    _ ______ _      _\n|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |\n| \  / | | | |  \| | | | | |___ | |__| | |__  | |    | |\n| |\/| | | | | .   | | |  \___ \|  __  |  __| | |    | |\n| |  | |_| |_| |\  |_| |_ ____| | |  | | |____| |____| |____ \n|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|"

.PHONY: all clean fclean re
