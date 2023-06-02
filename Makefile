NAME = minishell

SRC = src/error.c src/exit.c src/funny_graph.c src/main.c src/prompt.c src/get_to_display.c

PARSING = src/parsing/parse_command.c src/parsing/parse_env.c src/parsing/utils/utils_parse_command.c src/parsing/create_env.c src/parsing/file_in_out.c src/parsing/utils/ft_split_mini.c src/parsing/clean_cmd_redirect.c src/parsing/hear_append.c src/parsing/utils/get_args.c  src/parsing/clean_cmd_redirect_s.c src/parsing/utils/cpy_fd.c

EXECUTION = src/exec/use_builtin.c src/exec/exec.c src/exec/convert_env.c src/exec/find_path.c src/exec/check_redirections.c src/exec/heredoc.c src/exec/exec_command.c

BUILTINS = src/builtins/echo.c src/builtins/export.c src/builtins/cd.c src/builtins/env.c src/builtins/exit_builtin.c src/builtins/pwd.c src/builtins/unset.c src/builtins/clean_path.c

SRCS = $(SRC) $(EXECUTION) $(PARSING) $(BUILTINS)

OBJS_DIR = obj/

OBJS = $(SRCS:%.c=$(OBJS_DIR)%.zizi)

LIBS = libs/libft/libft.a

HEADER = headers/minishell.h headers/proto.h headers/struct.h

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

CC = cc

all: libft $(NAME) norm funny_graph

$(OBJS_DIR)%.zizi: %.c $(HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@ -Iheaders
	@printf	"\033[1;33m \r\033[2KCreating -c $< -o $\n \033[0m"

libft:
	@make -sC libs/libft

$(NAME): $(LIBS) $(OBJS) $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -Iheaders -lreadline -o $(NAME)
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
	@printf " __  __ _____ _   _ _____  _____ _    _ ______ _      _\n|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |\n| \  / | | | |  \| | | | | |___ | |__| | |__  | |    | |\n| |\/| | | | | .   | | |  \___ \|  __  |  __| | |    | |\n| |  | |_| |_| |\  |_| |_ ____| | |  | | |____| |____| |____ \n|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n"

.PHONY: all clean fclean re
