# SRC AND OBJ 
SRCS	= src/exec.c

OBJS	= $(addprefix $(OBJ_FOLDER)/, $(notdir $(SRCS:.c=.o)))

# FOLDERS
INCLUDE_FOLDER	= headers
LIBFT_FOLDER	= libs/libft
OBJ_FOLDER = obj

HEADERS	= $(INCLUDE_FOLDER)/liste.h $(INCLUDE_FOLDER)/minishell.h

# LIBRARY
LIBFT	= libft/libft.a

# COMPILATION
CC	= cc
CFLAGS	= -Wall -Wextra -Werror

# NAME
NAME	= minishell 

# COMMANDS
$(OBJ_FOLDER)/%.o: src/%.c
	${CC} -I$(INCLUDE_FOLDER) $(MLX_INC) -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(LIBFT)
	${CC} $(CFLAGS) -o $@ $^ $(LIBFT)

$(LIBFT):
	make -C libft

clean :
	rm -rf $(OBJ_FOLDER)/*.o
	make clean -C libft
	make clean -C $(MLX_PATH)

fclean : clean
	rm -f $(LIBFT)	
	rm -f $(NAME)
	rm -f $(MLX_LIB)

re : fclean all

.PHONY: all clean fclean re