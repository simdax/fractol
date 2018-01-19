/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:07:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/19 19:19:35 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void print_p(t_point point, int nb)
{
	printf("%d : %f et %f\n", nb, point.x, point.y);
	fflush(stdout);
}

t_point		proj_ortho(int nb, const t_map *z_points)
{
	int cols = z_points->cols;
	int rows = z_points->rows;
	int z = z_points->values[nb];
	float offset_x;
	float offset_y;
	float width;
	float heigth;
	t_point point;

	offset_x = 300;
	offset_y = 300;
	width = ((SIZE_X) / (cols - 1)) / 5;
	heigth = ((SIZE_Y) / (rows - 1)) / 5;
	float x = (offset_x + (width * (nb % cols)));
	float y = (offset_y + (heigth * (nb / cols)));
	point = (t_point){
		//x, y,
		
		/* x * sqrt(2) / 4 + y, */
		/* x * -sqrt(2) / 4 - z, */

		x * z_points->c1 - y * z_points->c2,
		offset_y + x * 1 / z_points->c1 + y * 2 / z_points->c2 - z * 5,

		z};
	return (point);
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
	matrix->map->c1 = 1;
	matrix->map->c2 = 2;

	matrix->len = z_points->len;
	matrix->cols = z_points->cols;
	matrix->rows = z_points->rows;
	res = (t_point*)malloc(sizeof(t_point) * nb);
	while (--nb >= 0)
		res[nb] = proj_ortho(nb, matrix->map);
	matrix->points = res;
	return (1);
}
