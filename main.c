/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/28 12:14:08 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	point_from_index(int nb, int space, int rows, int cols)
{
	return ((t_point){
			(OFFSET_X + space * (nb % rows)),
			(OFFSET_Y + space * (nb / cols)),
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

void	draw(t_matrix *matrix, long color, t_libx *libx)
{
	int 	i;
	int 	nb;
	int 	rows;
	t_point	*points;
	
	i = 0;
	nb = matrix->len;
	rows = matrix->rows;
	points = matrix->points;
	while (i < nb - 1)
	{
		if (i % rows != rows - 1)
			line(points[i], points[i + 1], color, libx);
		if (i < nb - rows)
			line(points[i], points[i + rows], color, libx);
		++i;
	}
}

int		main(void)
{
	t_libx		libx;
	t_point 	*points;
	t_matrix 	matrix;
	t_prog		prog;
	
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, 400, 400, "fdf");
	points = tab_of_points(20, 20, 4, 4);
	matrix = (t_matrix){20, 4, 4, points};
	prog = (t_prog){&libx, &matrix};
	draw(&matrix, 0x0000FF, &libx);
	mlx_key_hook(libx.win, transform, &prog);
	mlx_loop(libx.mlx);
	free(points);
}
