NAME = minishell

SRCS = src/error.c src/exec.c src/exit.c src/funny_graph.c src/main.c src/prompt.c src/parsing/parse_command.c src/parsing/parse_env.c src/parsing/utils_parse_command.c src/parsing/create_env.c

OBJS_DIR = obj/

OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

LIBS = libs/libft/libft.a

HEADER = headers/minishell.h headers/proto.h headers/struct.h

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

CC = cc

all: libft $(NAME) norm

$(OBJS_DIR)%.o: %.c $(HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf	"\033[1;33m \r\033[2K Creating -c $< -o $\n \033[0m"

libft:
	@make -sC libs/libft

$(NAME): $(LIBS) $(OBJS) $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME)
	@printf	"\033[1;32m \r\033[2K Compiling $(NAME) : DONE \n \033[0m"

norm:
	@norminette | grep 'Error' | echo "norm error" || echo "Tu es un geni"
	

clean:
	@make clean -sC libs/libft
	@$(RM) $(OBJS)
	@printf	"\033[1;31mDeleting objects : DONE \033[1;31m\n"

fclean: clean
	@make fclean -sC libs/libft
	@$(RM) $(NAME)
	@printf "\033[1;31mDeleting executable : DONE \033[1;31m\n\n"

re: fclean all

.PHONY: all clean fclean re
