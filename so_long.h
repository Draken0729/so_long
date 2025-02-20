/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:51:18 by quentin           #+#    #+#             */
/*   Updated: 2025/02/20 16:08:48 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define WIDTH 1000
# define HEIGHT 750

#ifndef TILE_SIZE
# define TILE_SIZE 64
#endif

# include "GNL/get_next_line.h"
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
    void    *img;
    void    *mlx;
    void    *win;
    char    **map;
    int     map_width;
    int     map_height;
    
    int     player_x;
    int     player_y;
    int     collectibles;
    int     collected;
    int     moves;
    int     exit_x;
    int     exit_y;
    
    struct s_textures
    {
        void *wall;
        void *floor;
        void *player;
        void *collectible;
        void *exit;
    } textures;
} t_game;

int             loop_hook(void *param);
void            close_game(t_game *game);
int             close_game_hook(void *param);
int             key_hook(int keycode, t_game *game);
char            **read_map(char *filename, t_game *game);
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
void            find_player_position(t_game *game);
void            count_collectibles(t_game *game);


#endif