/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:40:46 by quentin           #+#    #+#             */
/*   Updated: 2025/02/19 17:06:10 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void flood_fill(char **map, int x, int y, char **visited)
{
    if (map[y][x] == '1' || visited[y][x] == '1')
        return;

    visited[y][x] = '1';

    flood_fill(map, x + 1, y, visited);
    flood_fill(map, x - 1, y, visited);
    flood_fill(map, x, y + 1, visited);
    flood_fill(map, x, y - 1, visited);
}

void check_accessibility(char **map)
{
    int x;
    int y;
    int width = ft_strlen(map[0]);
    int height = 0;
    char **visited;
    int player_x = -1, player_y = -1;
    
    while (map[height])
        height++;

    visited = malloc(sizeof(char *) * (height + 1));
    if (!visited)
        error_exit("Erreur d'allocation mémoire.");
    
    y = 0;
    while(y < height)
    {
        visited[y] = ft_strdup(map[y]);
        if (!visited[y])
            error_exit("Erreur d'allocation mémoire.");
		y++;
    }
    visited[height] = NULL;

    y = 0;
    while(y < height)
    {
        x = 0;
        while(x < width)
        {
            if (map[y][x] == 'P')
            {
                player_x = x;
                player_y = y;
                break;
            }
			x++;
        }
        if (player_x != -1)
            break;
        y++;
    }

    flood_fill(map, player_x, player_y, visited);

    if (player_x == -1 || player_y == -1)
    error_exit("Le joueur (P) est introuvable sur la carte.");
    
    y = 0;
    while(y < height)
    {
        x = 0;
        while(x < width)
        {
            if ((map[y][x] == 'C' || map[y][x] == 'E') && visited[y][x] != '1')
                error_exit("Tous les collectibles et la sortie ne sont pas accessibles.");
			x++;
        }
		y++;
    }

    y = 0;
    while(y < height)
	{
        free(visited[y]);
		y++;
	}
    free(visited);
}
void check_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("Erreur lors de l'initialisation de la MLX.");

    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, game->map_height * TILE_SIZE, "so_long");
    if (!game->win)
        error_exit("Erreur lors de la création de la fenêtre.");
}
void free_map(char **map)
{
    int i = 0;
    if (!map)
        return;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void free_game(t_game *game)
{
    if (game->map)
        free_map(game->map);

    if (game->mlx && game->win)
        mlx_destroy_window(game->mlx, game->win);

    if (game->textures.player)
        mlx_destroy_image(game->mlx, game->textures.player);
    
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
}
