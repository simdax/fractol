/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:51:57 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/15 10:10:01 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			gros_malloc(t_map **map, int **res, char *file_name)
{
	int	fd;

	*map = malloc(sizeof(t_map));
	**map = (t_map){.len = 0, .rows = 0};
	if (!(*res = (int*)malloc(sizeof(int) * 1000000)) ||
		(fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	ft_bzero(*res, 1000000);
	return (fd);
}

static int	check(char *file)
{
	char	*msg;
	char	*buffer;
	int		fd;
	int		ret;

	buffer = (char*)malloc(64);
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		while ((ret = read(fd, buffer, 64)) > 0)
		{
			while (*buffer)
			{
				if (!ft_strchr("0123456789 \n,xabcdefgABCDEFG", *buffer))
				{
					msg = "Need a valid file of a grid of numbers. Pervert.\n";
					write(2, msg, ft_strlen(msg));
					return (0);
				}
				++buffer;
			}
			buffer -= 64;
		}
	}
	free(buffer);
	return (ret == 0);
}

static int	check_rows(t_map *map)
{
	static int size = 0;

	++size;
	if (!map->rows)
		map->cols = map->len;
	if (map->len / size != map->cols)
		return (0);
	return (1);
}

t_map		*parse(char *file_name)
{
	int		fd;
	char	*line;
	char	**split;
	int		*res;
	t_map	*map;

	if (!(fd = gros_malloc(&map, &res, file_name)) || !check(file_name))
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		while (*split)
		{
			res[map->len] = ft_atoi(*split++);
			++map->len;
		}
		if (!(check_rows(map)))
			return (0);
		++map->rows;
		ft_free_strsplit(split - map->cols);
		free(line);
	}
	map->values = res;
	return (map);
}
