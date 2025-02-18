/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:17:22 by quentin           #+#    #+#             */
/*   Updated: 2025/02/18 14:07:29 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int handle_keypress(int keycode, t_game *game)
{
    if (keycode == XK_Escape) // Touche Échap pour quitter
    {
        free_game(game);
        exit(0);
    }
    else if (keycode == XK_w || keycode == XK_Up) // Haut
        move_player(game, 0, -1);
    else if (keycode == XK_s || keycode == XK_Down) // Bas
        move_player(game, 0, 1);
    else if (keycode == XK_a || keycode == XK_Left) // Gauche
        move_player(game, -1, 0);
    else if (keycode == XK_d || keycode == XK_Right) // Droite
        move_player(game, 1, 0);

    return (0);
}
void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    if (game->map[new_y][new_x] == '1') // Mur => impossible
        return;

    if (game->map[new_y][new_x] == 'C') // Collectible => récupérer
    {
        game->collectibles--;
        game->map[new_y][new_x] = '0'; // Supprime le collectible
    }

    if (game->map[new_y][new_x] == 'E' && game->collectibles == 0) // Sortie
    {
        ft_printf("Bravo ! Vous avez gagné !\n");
        free_game(game);
        exit(0);
    }

    game->map[game->player_y][game->player_x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player_x = new_x;
    game->player_y = new_y;

    render_map(game);
}
