/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:51:57 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/02 16:08:25 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			gros_malloc(t_map **map, int **res, char *file_name)
{
	int	fd;

	*map = malloc(sizeof(t_map));
	**map = (t_map){.len = 0, .rows = 0};
	if (!(*res = (int*)malloc(sizeof(int) * 1000000)) ||
		((fd = open(file_name, O_RDONLY)) == -1))
		return (0);
	ft_bzero(*res, 1000000);
	return (fd);
}

t_map		*parse(char *file_name)
{
	int		fd;
	char	*line;
	char	**split;
	int		*res;
	t_map	*map;

	if (!(fd = gros_malloc(&map, &res, file_name)))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		while (*split)
		{
			res[map->len] = ft_atoi(*split++);
			++map->len;
		}
		if (!map->rows)
			map->cols = map->len;
		++map->rows;
		free_strsplit(split - map->cols);
		free(line);
	}
	map->values = res;
	return (map);
}
