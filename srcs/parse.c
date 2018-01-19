/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:51:57 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/19 10:39:53 by scornaz          ###   ########.fr       */
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
	char *line;
	char *cpy;
	int ret;
	int fd;

	fd = open(file, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		cpy = line;
		while (*line)
		{
			if (!ft_strchr("0123456789 \n,xabcdefgABCDEFG", *line))
			{
				write(2, "need a squared grid\n", 20);
				return (0);
			}
			++line;
		}
		free(cpy);
	}
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
