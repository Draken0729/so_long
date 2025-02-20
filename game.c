/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:17:22 by quentin           #+#    #+#             */
/*   Updated: 2025/02/20 16:32:15 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int loop_hook(void *param)
{
    t_game *game;

    game = (t_game *)param;
    render_map(game);
    return (0);
}


int handle_keypress(int keycode, t_game *game)
{
    if (keycode == 65307)
    {
        free_game(game);
        exit(0);
    }
    else if (keycode == 119 || keycode == 65362)
        move_player(game, 0, -1);
    else if (keycode == 115 || keycode == 65364)
        move_player(game, 0, 1);
    else if (keycode == 97 || keycode == 65361)
        move_player(game, -1, 0);
    else if (keycode == 100 || keycode == 65363)
        move_player(game, 1, 0);

    return (0);
}
void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    if (game->map[new_y][new_x] == '1')
        return;

    if (game->map[new_y][new_x] == 'C')
    {
        game->collected++;
        game->map[new_y][new_x] = '0';
    }

    if (game->map[new_y][new_x] == 'E')
    {
        if (game->collected == game->collectibles)
        {
            ft_printf("Congratulations! You win!\n");
            free_game(game);
            exit(0);
        }
        else
        {
            return;
        }
    }

    if (game->map[game->player_y][game->player_x] == 'P' && game->exit_x == game->player_x && game->exit_y == game->player_y)
        game->map[game->player_y][game->player_x] = 'E';
    else
        game->map[game->player_y][game->player_x] = '0';

    game->map[new_y][new_x] = 'P';
    game->player_x = new_x;
    game->player_y = new_y;

    game->moves++;

    ft_printf("%d\n", game->moves);

    render_map(game);
}


void find_player_position(t_game *game)
{
    int y = 0;
    while (game->map[y])
    {
        int x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == 'P')
            {
                game->player_x = x;
                game->player_y = y;
                return;
            }
            x++;
        }
        y++;
    }
}
void count_collectibles(t_game *game)
{
    int x, y;

    game->collectibles = 0;
    game->collected = 0;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == 'C')
                game->collectibles++;
            x++;
        }
        y++;
    }
}
