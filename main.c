/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/27 17:12:59 by scornaz          ###   ########.fr       */
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

	res = (t_point*)malloc(sizeof(t_point) * nb);
	while (--nb >= 0)
	{
		res[nb] = point_from_index(nb, space, rows, cols);
		printf("point nb%d: %d et %d \n", nb, res[nb].x, res[nb].y);
	}
	return (res);
}

void	link(t_point *points, int nb, int rows, t_libx *libx)
{
	int i =0;
	
	while (i < nb - 1)
	{
		if (i % rows != rows - 1)
			line(points[i], points[i + 1], libx);
		if (i < nb - rows) 
		{ 
			line(points[i], points[i + rows], libx);
		}
		++i;
	}
}

#define ll(a,b, c, d)	line((t_point){a, b}, (t_point){c, d}, &libx);

int		main()
{
	t_libx	libx;
	
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, 400, 400, "fdf");
	t_point *points = collectionPoints(20, 20, 4, 4);
	link(points, 20, 4, &libx);
//	ll(10, 10, 10, 30);
//	ll(30, 10, 30, 30);
//	ll(50, 10, 50, 30);
//	ll(70, 10, 70, 30);
//	ll(90, 10, 90, 30);
	mlx_loop(libx.mlx);
}
