/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:32:03 by quentin           #+#    #+#             */
/*   Updated: 2025/02/19 16:59:26 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char **read_map(char *filename, t_game *game)
{
    int count_height;
    int fd;
    char *line;
    char **map;
    char *temp;
    
    count_height = 0;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        error_exit("Impossible d'ouvrir le fichier de la carte.");

    map = NULL;
    temp = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] == '\n') // Vérifie si une ligne vide est présente
            error_exit("Erreur : La carte contient une ligne vide.");

        temp = ft_strjoin(temp, line); // Concatène les lignes lues
        game->map_width = ft_strlen(line);
        free(line);
        count_height++;
    }
    game->map_height = count_height;

    close(fd);
    if (!temp)
        error_exit("Erreur : La carte est vide.");
    map = ft_split(temp, '\n'); // Transforme en tableau de lignes
    free(temp);
    return (map);
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

