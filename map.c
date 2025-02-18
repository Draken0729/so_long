/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:32:03 by quentin           #+#    #+#             */
/*   Updated: 2025/02/18 14:41:20 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void read_map(char *file)
{
    int fd = open(file, O_RDONLY);
    char buffer[1024];
    int bytes = read(fd, buffer, 1023);
    buffer[bytes] = '\0';
    printf("%s\n", buffer);
    close(fd);
}
void load_textures(t_game *game)
{
    int width;
    int height;

    game->textures.wall = mlx_xpm_file_to_image(game->mlx, "sprites/stone.xpm", &width, &height);
    if (!game->textures.wall)
        error_exit("Erreur lors du chargement du sprite mur.");

    game->textures.floor = mlx_xpm_file_to_image(game->mlx, "sprites/floor.xpm", &width, &height);
    if (!game->textures.floor)
        error_exit("Erreur lors du chargement du sprite sol.");

    game->textures.player = mlx_xpm_file_to_image(game->mlx, "sprites/fox.xpm", &width, &height);
    if (!game->textures.player)
        error_exit("Erreur lors du chargement du sprite joueur.");

    game->textures.collectible = mlx_xpm_file_to_image(game->mlx, "sprites/chicken.xpm", &width, &height);
    if (!game->textures.collectible)
        error_exit("Erreur lors du chargement du sprite collectible.");

    game->textures.exit = mlx_xpm_file_to_image(game->mlx, "sprites/exit.xpm", &width, &height);
    if (!game->textures.exit)
        error_exit("Erreur lors du chargement du sprite sortie.");
}
void render_map(t_game *game)
{
    int x, y;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            mlx_put_image_to_window(game->mlx, game->win, game->textures.floor, x * TILE_SIZE, y * TILE_SIZE);

            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.player, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.collectible, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.exit, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
}

