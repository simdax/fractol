/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:07:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/20 14:20:09 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		ortho(float x, float y, float z, t_matrix *matrix)
{
	return ((t_point){
			x * matrix->c1 - y * matrix->c2,
				x * 1 / matrix->c1 + y * 2 / matrix->c2 - z * 5,
				z});
}

t_point		projection(int nb, t_matrix *matrix)
{
	t_map	*z_points;
	float	x;
	float	y;

	z_points = matrix->map;
	x = ((z_points->width * (nb % z_points->cols)));
	y = ((z_points->height * (nb / z_points->cols)));
	return (matrix->proj_f(x, y, z_points->values[nb], matrix));
}

int			tab_of_points(char *file, t_matrix *matrix)
{
	t_point		*res;
	t_map		*z_points;
	int			nb;
	int			space;

	if (!(z_points = parse(file)))
		return (0);
	nb = z_points->len;
	matrix->map = z_points;
	matrix->c1 = 3;
	matrix->c2 = 1;
	matrix->map->width = ((SIZE_X) / (z_points->cols - 1)) / 5;
	matrix->map->height = ((SIZE_Y) / (z_points->rows - 1)) / 5;
	matrix->proj_f = ortho;
	matrix->height = matrix->map->height * matrix->map->cols +
		matrix->c1 * matrix->map->height;
	matrix->width = matrix->map->width * matrix->map->rows +
		matrix->c2 * matrix->map->width;
	res = (t_point*)malloc(sizeof(t_point) * nb);
	while (--nb >= 0)
		res[nb] = projection(nb, matrix);
	matrix->points = res;
	translate(matrix, (SIZE_X - matrix->width) / 2,
			(SIZE_Y - matrix->height) / 2);
	return (1);
}
