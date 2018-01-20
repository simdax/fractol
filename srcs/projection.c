/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:07:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/20 19:32:24 by scornaz          ###   ########.fr       */
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
	printf("%f et %f\n", x, y);
	return (matrix->proj_f(x, y, z_points->values[nb], matrix));
}

void		center_matrix(t_matrix *matrix)
{
	int cols;
	int rows;
	float x1;
	float x2;
	
	cols = matrix->map->cols;
	rows = matrix->map->rows;
	x1 = matrix->points[cols * (rows - 1)].x;
	x2 = matrix->points[cols - 1].x;
	matrix->width = (x2 + x1) / 2;
	x1 = matrix->points[cols * rows - 1].y;
	x2 = matrix->points[0].y;
	matrix->height = x1 - x2;
	translate(matrix, (SIZE_X / 2 - matrix->width), (SIZE_Y - matrix->height) / 2);
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
	matrix->map->width = matrix->map->width ? matrix->map->width : 1;
	matrix->map->height = matrix->map->height ? matrix->map->height : 1;
	matrix->proj_f = ortho;
	res = (t_point*)malloc(sizeof(t_point) * nb);
	while (--nb >= 0)
		res[nb] = projection(nb, matrix);
	matrix->points = res;
	center_matrix(matrix);
	return (1);
}
