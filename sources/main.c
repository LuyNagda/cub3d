/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:08:11 by jbadaire          #+#    #+#             */
/*   Updated: 2024/04/24 17:42:42 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string_utils.h>

void	hooks(t_cub3d *data)
{
	//raycasting(data);
	mlx_hook(data->window, 17, 1L << 0, close_window, &data);
	mlx_hook(data->window, 2, 1L << 0, key_press, &data);
	//mlx_hook(data->window, 3, 0, key_release, &data);
	//mlx_loop_hook(data->mlx, &raycasting, &data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;
	int		return_state;
	int		value;

	if (argc < 2)
		return (printf("Error\n -> Invalid number of arguments.\n"), 0);
	return_state = handle_file_error(argv);
	if (return_state < 0)
		return (0);
	cub3d.map = malloc(sizeof(t_map));
	if (cub3d.map == NULL)
		return (printf("Error\n -> Can't load map.\n"), 0);
	cub3d.map->path = argv[1];
	cub3d.map->map = NULL;
	cub3d.mlx = NULL;
	load_file_content(&cub3d);
	value = init_graphics_part(&cub3d);
	if (value == -1)
		return (printf("Error\n -> Can't initialize mlx.\n"), 0);
	load_map(&cub3d, value);
	if (!map_is_valid(&cub3d))
		return (printf("Error\n -> Invalid map.\n"), free_and_exit(&cub3d), 0);
	if (ft_init(&cub3d))
		return (printf("Error\n -> Error initializing the game.\n"), free_and_exit(&cub3d), 0);
	hooks(&cub3d);
	//free_and_exit(&cub3d);
}

void	free_and_exit(t_cub3d *cub3d)
{
	//if (cub3d->file_content != NULL)
	//	ft_free_split(cub3d->file_content);
	
	for (int i = 0; cub3d->map->map[i]; i++)
		printf("%d %s \n", i, cub3d->map->map[i]);
		
	//if (cub3d->map.map != NULL)
	//	ft_free_split(cub3d->map.map);
	//destroy_textures(cub3d);
	if (cub3d->mlx) {
		if (cub3d->window)
			mlx_destroy_window(cub3d->mlx, cub3d->window);
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
	}
	exit(0);
}
