NAME = so_long
MLX = minilibx/libmlx.a
libft = libft/libft.a
ft_printf = ft_printf/ft_printf.a
GNL = GNL/get_next_line.c GNL/get_next_line_utils.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c map.c game.c error1.c error2.c $(GNL)
OBJ = $(SRC:.c=.o)
LIBS = -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(libft) $(ft_printf) 
		 $(CC) $(CFLAGS) $(OBJ) $(MLX) $(libft) $(ft_printf)  $(LIBS) -o $(NAME)
$(MLX):
		make -C minilibx
$(libft):
		make -C libft
$(ft_printf):
		make -C ft_printf


%.o: %.c	
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C ft_printf fclean
re: fclean all

run: re
	valgrind ./$(NAME)