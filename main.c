/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/28 12:12:09 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define OFFSET_X	10
#define OFFSET_Y	10

typedef struct	s_matrix
{
	int			len;
	int			cols;
	int			rows;
	t_point		*points;
}				t_matrix;
	
typedef struct	s_prog
{
	t_libx		*libx;
	t_matrix	*matrix;
}				t_prog;

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

int		transform(int keycode, void *arg)
{
	t_prog	*prog;
	int 	len;
	
	prog =	(t_prog*)arg;
	len = prog->matrix->len;
	draw(prog->matrix, 0x000000, prog->libx);
	while (--len >= 0)
		prog->matrix->points[len].x += 1;
	draw(prog->matrix, 0x00FF00, prog->libx);
	return (0);
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
