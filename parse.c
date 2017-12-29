/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:51:57 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/29 12:37:41 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

t_map			*parse(void)
{
	int 	fd;
	char	*line;
	char	**split;
	int		*res;
	t_map	*map;
	
	map = malloc(sizeof(t_map));
	*map = (t_map){.len = 0, .rows = 0};
	res = (int*)malloc(sizeof(int) * 300);
	fd = open("maps/42.fdf", O_RDONLY);
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

t_point		point_from_index(int nb, int space, int rows, int cols)
{	
	return ((t_point){
			OFFSET_X + space * (nb % cols) - (space * (nb / cols)),
			OFFSET_Y + space * (nb / cols),
			0});
}

int			tab_of_points(int space, t_matrix *matrix)
{
	t_point 	*res;
	t_map		*z_points;
	int	       	nb;
	
	if (!(z_points = parse()))
		return (0);
	nb = z_points->len;
	res = (t_point*)malloc(sizeof(t_point) * nb);
	while (--nb >= 0)
	{
		res[nb] = point_from_index(nb, space, z_points->rows, z_points->cols);
		res[nb].z = z_points->values[nb];
		res[nb].y -= res[nb].z * (space / 2);
	}
	matrix->len = z_points->len;
	matrix->cols = z_points->cols;
	matrix->rows = z_points->rows;
	matrix->points = res;
	free(z_points->values);
	free(z_points);
	return (1);
}
