SRCS	= src/exec.c
INCLUDE_FOLDER	= includes

HEADERS	= includes/fdf.h includes/get_next_line.h includes/libft.h

OBJ_FOLDER = obj
OBJS	= $(addprefix $(OBJ_FOLDER)/, $(notdir $(SRCS:.c=.o)))

NAME	= minishell 

CC	= cc
CFLAGS	= -Wall -Wextra -Werror

LIBFT	= libft/libft.a

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