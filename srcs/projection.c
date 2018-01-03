/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:07:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/02 16:44:38 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		proj_ortho(int nb, int space, int cols)
{
	return ((t_point){
			OFFSET_X + (space / (2)) * (nb % cols) - (space * (nb / cols)),
				OFFSET_Y + (space) * (nb / cols) + (space * (nb % cols)),
			0});
}

void		z_proj(int nb, t_point *points, int space, t_map *z_points)
{
	points[nb] = proj_ortho(nb, space, z_points->cols);
	points[nb].z = z_points->values[nb];
	points[nb].y -= points[nb].z * (space / 10);
}

int			tab_of_points(char *file, int space, t_matrix *matrix)
{
	t_point		*res;
	t_map		*z_points;
	int			nb;

	if (!(z_points = parse(file)))
		return (0);
	nb = z_points->len;
	res = (t_point*)malloc(sizeof(t_point) * nb);
	while (--nb >= 0)
		z_proj(nb, res, space, z_points);
	matrix->len = z_points->len;
	matrix->cols = z_points->cols;
	matrix->rows = z_points->rows;
	matrix->points = res;
	free(z_points->values);
	free(z_points);
	return (1);
}
