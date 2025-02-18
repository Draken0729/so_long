/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:51:18 by quentin           #+#    #+#             */
/*   Updated: 2025/02/18 14:46:41 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define WIDTH 1000
# define HEIGHT 750

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include "minilibx/mlx_int.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h> 

typedef struct s_game
{
    void    *map;
    void    *mlx;
    void    *win;
	t_img	*img;
	
}    t_game;

int             loop_hook(t_game *game);
void            read_map(char *file);
int				ft_putstr(char *s);
int				ft_putnbr(int n);
int				ft_putchar(char c);
unsigned int	ft_printhex_min(unsigned int nombre);
unsigned int	ft_printhex_maj(unsigned int nombre);
int				ft_print_pointer(void *ptr);
int				ft_putunbr(unsigned int n);
int				ft_printf(const char *format, ...);
void            render_map(t_game *game);
void            load_textures(t_game *game);
int             handle_keypress(int keycode, t_game *game);
void            move_player(t_game *game, int dx, int dy);
void            flood_fill(char **map, int x, int y, char **visited);
void            check_accessibility(char **map);
void            check_mlx(t_game *game);
void            free_map(char **map);
void            free_game(t_game *game);
void            error_exit(char *message);
void            error_prog(int argc, char *filename);
void            error_map(char **map);
void            check_walls(char **map);


#endif