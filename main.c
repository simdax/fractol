/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/28 19:06:10 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	if (!(points = tab_of_points(20, &matrix)))
	{
		printf("error with map\n");
		return (1);
	}
	prog = (t_prog){&libx, &matrix};
	draw(&matrix, 0x0000FF, &libx);
	mlx_key_hook(libx.win, transform, &prog);
	mlx_loop(libx.mlx);
	free(points);
	return (0);
}
