# SRC AND OBJ 
SRCS	= src/exec.c src/main.c src/error.c src/funny_graph.c src/prompt.c src/exit.c src/parsing/parse_command.c src/parsing/parse_env.c src/parsing/utils_parse_command.c

OBJS	= $(addprefix $(OBJ_FOLDER)/, $(SRCS:.c=.o))

# FOLDERS
INCLUDE_FOLDER	= headers
LIBFT_FOLDER	= libs/libft
OBJ_FOLDER = obj

HEADERS	= $(INCLUDE_FOLDER)/struct.h $(INCLUDE_FOLDER)/minishell.h $(INCLUDE_FOLDER)/proto.h

# LIBRARY
LIBFT	= libs/libft/libft.a

# COMPILATION
CC	= cc
CFLAGS	= -Wall -Wextra -Werror -lreadline

# NAME
NAME	= minishell 

# COMMANDS
$(OBJ_FOLDER)/%.o: src/%.c
	${CC} -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(LIBFT)
	${CC} $(CFLAGS) -o $@ $^ $(LIBFT)

$(LIBFT):
	make -sC $(LIBFT_FOLDER)

clean :
	rm -rf $(OBJ_FOLDER)/*.o
	make clean -sC $(LIBFT_FOLDER)

fclean : clean
	rm -f $(LIBFT)	
	rm -f $(NAME)


re : fclean all

.PHONY: all clean fclean re