/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:32:03 by quentin           #+#    #+#             */
/*   Updated: 2025/02/20 19:02:05 by quentin          ###   ########.fr       */
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
        error_exit("Unable to open the map file.");

    map = NULL;
    temp = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] == '\n')
            error_exit("Error: The card contains a blank line.");
        temp = ft_strjoin(temp, line);
        game->map_width = ft_strlen(line);
        free(line);
        count_height++;
    }
    game->map_height = count_height;

    close(fd);
    if (!temp)
        error_exit("Error : empty map.");
    map = ft_split(temp, '\n');
    free(temp);
    return (map);
}

void load_textures(t_game *game)
{
    int width;
    int height;

    game->textures.wall = mlx_xpm_file_to_image(game->mlx, "sprites/stone.xpm", &width, &height);
    if (!game->textures.wall)
        error_exit("Error loading wall.");

    game->textures.floor = mlx_xpm_file_to_image(game->mlx, "sprites/floor.xpm", &width, &height);
    if (!game->textures.floor)
        error_exit("Error loading floor.");

    game->textures.player = mlx_xpm_file_to_image(game->mlx, "sprites/fox.xpm", &width, &height);
    if (!game->textures.player)
        error_exit("Error loading player.");

    game->textures.collectible = mlx_xpm_file_to_image(game->mlx, "sprites/chicken.xpm", &width, &height);
    if (!game->textures.collectible)
        error_exit("Error loading collectible.");

    game->textures.exit = mlx_xpm_file_to_image(game->mlx, "sprites/exit.xpm", &width, &height);
    if (!game->textures.exit)
        error_exit("Error loading exit.");
}
void render_map(t_game *game)
{
    int x;
    int y;
    
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            mlx_put_image_to_window(game->mlx, game->win, game->textures.floor, x * TILE_SIZE, y * TILE_SIZE);

            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'E')
            {
                mlx_put_image_to_window(game->mlx, game->win, game->textures.exit, x * TILE_SIZE, y * TILE_SIZE);
                game->exit_x = x;
                game->exit_y = y;
            }
            else if (game->map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.player, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.collectible, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
}

