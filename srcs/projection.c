/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:07:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/19 14:31:01 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

print_p(t_point point, int nb)
{
	printf("%d : %f et %f\n", nb, point.x, point.y);
	fflush(stdout);
}

t_point		proj_ortho(int nb, int cols, int rows, int z)
{
	float offset_x;
	float offset_y;
	float width;
	float heigth;
	t_point point;
	
	offset_y = (SIZE_Y / 10);
	offset_x = (SIZE_X / 10);
	width = (SIZE_X - offset_x * 2) / (rows - 1);
	heigth = (SIZE_Y - offset_y * 2) / (cols - 1);
	float x = (offset_x + (width * (nb % cols)));
	float y = (offset_y + (heigth * (nb / cols)));
	point = (t_point){
		x * 1 - y * 2,
		z + x * 1/2 + y * 2 / 2,  
		z};
//	print_p(point, nb);
	return (point);
}

void		z_proj(int nb, t_point *points, t_map *z_points)
{
	points[nb] = proj_ortho(nb, z_points->cols, z_points->rows, z_points->values[nb]);
//	points[nb].y -= points[nb].z * (5);
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
	res = (t_point*)malloc(sizeof(t_point) * nb);
	while (--nb >= 0)
		z_proj(nb, res, z_points);
	matrix->len = z_points->len;
	matrix->cols = z_points->cols;
	matrix->rows = z_points->rows;
	matrix->points = res;
	free(z_points->values);
	free(z_points);
	return (1);
}
