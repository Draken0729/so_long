/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:12:18 by quentin           #+#    #+#             */
/*   Updated: 2025/02/20 16:09:32 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void close_game(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->map);
    free(game->mlx);
    exit(0);
}
int close_game_hook(void *param)
{
    t_game *game = (t_game *)param;
    close_game(game);
    return (0);
}
int main(int argc, char **argv)
{
    t_game game;

    error_prog(argc, argv[1]);
        
    game.map = read_map(argv[1], &game);
    count_collectibles(&game);
    error_map(game.map);
    check_walls(game.map);
    check_accessibility(game.map);

    check_mlx(&game);
    load_textures(&game);

    render_map(&game);
    game.moves = 0;

    mlx_hook(game.win, 17, 0, close_game_hook, &game);
    mlx_key_hook(game.win, handle_keypress, &game);
    find_player_position(&game);
    render_map(&game);

    mlx_loop(game.mlx);

    return (0);
}
