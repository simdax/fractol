/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/27 17:20:07 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	point_from_index(int nb, int space, int rows, int cols)
{
	int offset_x;
	int offset_y;

	offset_x = 10;
	offset_y = 10;
	return ((t_point){(offset_x + space * (nb % rows)),
			(offset_y + space * (nb / cols)),
			0});
}

t_point	*tab_of_points(int nb, int space, int rows, int cols)
{
	t_point *res;

	res = (t_point*)malloc(sizeof(t_point) * nb);
	while (--nb >= 0)
		res[nb] = point_from_index(nb, space, rows, cols);
	return (res);
}

void	link(t_point *points, int nb, int rows, t_libx *libx)
{
	int i;

	i = 0;
	while (i < nb - 1)
	{
		if (i % rows != rows - 1)
			line(points[i], points[i + 1], libx);
		if (i < nb - rows)
			line(points[i], points[i + rows], libx);
		++i;
	}
}

int		main(void)
{
	t_libx	libx;
	t_point *points;

	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, 400, 400, "fdf");
	points = tab_of_points(20, 20, 4, 4);
	link(points, 20, 4, &libx);
	mlx_loop(libx.mlx);
}
