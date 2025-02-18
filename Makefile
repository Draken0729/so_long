NAME = so_long
MLX = minilibx/libmlx.a
ft_printf = ft_printf/ft_print.a
libft = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c map.c game.c error1.c error2.c
OBJ = $(SRC:.c=.o)
LIBS = -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(ft_printf) $(libft)
		 $(CC) $(CFLAGS) $(OBJ) $(MLX) $(ft_printf) $(libft) $(LIBS) -o $(NAME)
$(MLX):
		make -C minilibx
$(ft_printf):
		make -C ft_printf
$(libft):
		make -C libft

%.o: %.c	
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

run: re
	valgrind ./$(NAME)