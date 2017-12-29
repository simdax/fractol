/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/29 15:13:51 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		transform(int keycode, void *arg)
{
	t_prog			*prog;

	prog = (t_prog*)arg;
	draw(prog->matrix, 0x000000, prog->libx);
	event_manager(keycode, prog->matrix);
	draw(prog->matrix, 0x00FF00, prog->libx);
	return (0);
}

void	draw(t_matrix *matrix, long color, t_libx *libx)
{
	int		i;
	int		nb;
	int		rows;
	int		cols;
	t_point	*points;

	i = 0;
	nb = matrix->len;
	rows = matrix->rows;
	cols = matrix->cols;
	points = matrix->points;
	while (i < nb - 1)
	{
		if (i % cols != cols - 1)
			line(points[i], points[i + 1], color, libx);
		if (i < nb - cols)
			line(points[i], points[i + cols], color, libx);
		++i;
	}
}

int		main(int argc, char **argv)
{
	t_libx		libx;
	t_matrix	matrix;
	t_prog		prog;

	if (argc > 1 && !tab_of_points(argv[1], SPACE, &matrix))
	{
		printf("error with map\n");
		return (1);
	}
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, SIZE_X, SIZE_Y, "fdf");
	prog = (t_prog){&libx, &matrix};
	draw(&matrix, 0x00FF00, &libx);
	mlx_key_hook(libx.win, transform, &prog);
	mlx_loop(libx.mlx);
	free(matrix.points);
	return (0);
}
