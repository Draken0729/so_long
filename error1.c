/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:29:37 by quentin           #+#    #+#             */
/*   Updated: 2025/02/19 16:09:57 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void error_exit(char *message)
{
	ft_printf("Error\n%s\n", message);
	exit(EXIT_FAILURE);
}

void error_prog(int argc, char *filename)
{
	int fd;

	if (argc != 2)
		error_exit("Nombre d'arguments invalide. Usage : ./so_long <map.ber>");

	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".ber", 4) != 0)
		error_exit("Le fichier doit avoir l'extension .ber");

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("Impossible d'ouvrir le fichier.");
	close(fd);
}

void error_map(char **map)
{
	int x;
	int y;
	int player_count;
	int exit_count;
	int collect_count;

	player_count = 0;
	exit_count = 0;
	collect_count = 0;

	if (!map)
		error_exit("Carte non valide.");

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				player_count++;
			else if (map[y][x] == 'E')
				exit_count++;
			else if (map[y][x] == 'C')
				collect_count++;
			else if (map[y][x] != '1' && map[y][x] != '0')
				error_exit("Caractère invalide dans la carte.");
			x++;
		}
		y++;
	}

	if (player_count != 1)
		error_exit("Il doit y avoir exactement un joueur sur la carte.");
	if (exit_count != 1)
		error_exit("Il doit y avoir exactement une sortie sur la carte.");
	if (collect_count < 1)
		error_exit("Il doit y avoir au moins un collectible.");
}
void check_walls(char **map)
{
    int x; 
	int y;
    int width = ft_strlen(map[0]);
    int height = 0;
	
	x = 0;
	y = 0;
    while (map[height])
        height++;

    while(x < width)
    {
        if (map[0][x] != '1' || map[height - 1][x] != '1')
            error_exit("La carte n'est pas entourée de murs.");
		x++;
    }

    while(y < height)
    {
        if (map[y][0] != '1' || map[y][width - 1] != '1')
            error_exit("La carte n'est pas entourée de murs.");
		y++;
    }
}
