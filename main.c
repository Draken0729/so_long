/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:12:18 by quentin           #+#    #+#             */
/*   Updated: 2025/02/18 14:47:11 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
	t_game game;
	
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Ma fenêtre");
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);

    error_prog(argc, argv[1]);
    game.map = read_map(argv[1]); // Fonction pour charger la carte
    error_map(game.map);
    check_walls(game.map);
    check_accessibility(game.map);
    check_mlx(&game);

    // Lancer le jeu
    mlx_loop(game.mlx);

    // Libérer la mémoire avant de quitter
    free_game(&game);

	mlx_hook(game.win, 17, 0, mlx_loop_end, game.mlx);

	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_loop(game.mlx);
	
	mlx_destroy_image(game.mlx, game.img);
	mlx_destroy_window(game.mlx, game.win);
	mlx_destroy_display(game.mlx);
	read_map("map.ber");
	free(game.mlx);
    return (0);
}