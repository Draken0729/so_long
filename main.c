/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:12:18 by quentin           #+#    #+#             */
/*   Updated: 2025/02/19 17:03:49 by quentin          ###   ########.fr       */
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
// Fonction de fermeture (wrapper) pour mlx_hook
int close_game_hook(void *param)
{
    t_game *game = (t_game *)param;
    close_game(game);
    return (0);  // retourne un int, comme l'attend mlx_hook
}
int key_hook(int keycode, t_game *game)
{
    if (keycode == 65307) // Touche ESC
        close_game(game);
    return (0);
}
int main(int argc, char **argv)
{
    t_game game;

    // Vérifier les erreurs de programme
    error_prog(argc, argv[1]);
        
    // Charger la carte et vérifier les erreurs
    game.map = read_map(argv[1], &game);
    error_map(game.map);
    check_walls(game.map);
    check_accessibility(game.map);

    check_mlx(&game);
    load_textures(&game);

    render_map(&game);

    mlx_hook(game.win, 17, 0, close_game_hook, &game);
    mlx_key_hook(game.win, key_hook, &game);

    mlx_loop(game.mlx);

    return (0);
}
