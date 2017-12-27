/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/27 14:27:42 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	point_from_index(int nb, int space, int rows, int cols)
{
	int x = 10;
	int y = 10;

	return ((t_point){(x + space * (nb % rows)),
			(y + space * (nb / cols)),
			0});
}

t_point	*collectionPoints(int nb, int space, int rows, int cols)
{
	t_point *res;

	res = (t_point*)malloc(sizeof(t_point) * (nb + 1));
	while (nb >= 0)
		res[nb--] = point_from_index(nb, space, rows, cols);
	return (res);
}

void	link(t_point *points, int nb, int rows, t_libx *libx)
{
	int i =0;
	
	while (i < nb - 1)
	{
		line(points[i], points[i + 1], libx);
		if (i < nb - rows)
			line(points[i], points[i + rows], libx);
	}
}

int		main()
{
	t_libx	libx;
	
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, 400, 400, "fdf");
	t_point *points = collectionPoints(20, 20, 4, 4);
//	link(points, 20, 4, &libx);
	line((t_point){20, 20}, (t_point){20, 40}, &libx);
	/* line((t_point){20, 40}, (t_point){30, 60}, &libx); */
	/* line((t_point){30, 60}, (t_point){220, 140}, &libx); */
	/* line((t_point){220, 140}, (t_point){20, 20}, &libx); */
	mlx_loop(libx.mlx);
}
