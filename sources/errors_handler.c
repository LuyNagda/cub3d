/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:30:48 by jbadaire          #+#    #+#             */
/*   Updated: 2024/05/06 14:01:01 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "string_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	handle_file_error(char *argv[])
{
	int	fd;

	if (!ft_endwith(argv[1], ".cub"))
		return (printf("Error\n -> Invalid file format.\n"), -2);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n -> Can't open file.\n");
		printf("please check permissions or path: %s\n", argv[1]);
		return (-3);
	}
	close(fd);
	return (1);
}

static t_boolean	all_direction_has_loaded(t_cub3d *cub3D)
{
	if (get_texture_by_direction(cub3D, NORTH) == NULL)
		return (_false);
	if (get_texture_by_direction(cub3D, SOUTH) == NULL)
		return (_false);
	if (get_texture_by_direction(cub3D, WEST) == NULL)
		return (_false);
	if (get_texture_by_direction(cub3D, EAST) == NULL)
		return (_false);
	return (_true);
}

t_boolean	textures_has_correctly_loaded(t_cub3d *cub3d)
{
	t_loaded_textures	*tmp;
	int					index;

	tmp = cub3d->textures;
	index = 0;
	while (tmp != NULL)
	{
		if (tmp->current_texture->texture == NULL)
			return (_false);
		tmp = tmp->next;
		index++;
	}
	if (index != 4)
		return (_false);
	if (!all_direction_has_loaded(cub3d))
		return (_false);
	return (_true);
}
