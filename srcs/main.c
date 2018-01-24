/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/24 17:40:00 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			transform(int keycode, void *arg)
{
	t_prog			*prog;

	prog = (t_prog*)arg;
	draw(prog->matrix, create_color(0, 0, 0), prog->libx);
	event_manager(keycode, prog->matrix);
	draw(prog->matrix, prog->color, prog->libx);
	mlx_put_image_to_window(prog->libx->mlx, prog->libx->win,
						prog->libx->img->ptr, 0, 0);
	return (0);
}

void		draw(t_matrix *matrix, t_color color, t_libx *libx)
{
	int		i;
	int		nb;
	int		rows;
	int		cols;
	t_point	*points;

	i = 0;
	nb = matrix->map->len;
	rows = matrix->map->rows;
	cols = matrix->map->cols;
	points = matrix->points;
	while (i < nb - 1)
	{
		if (i % cols < cols - 1)
			line(points[i], points[i + 1], color, libx);
		if (i < nb - cols)
			line(points[i], points[i + cols], color, libx);
		++i;
	}
}

static void	free_matrix(t_matrix *matrix)
{
	free(matrix->map->values);
	free(matrix->map);
	free(matrix->points);
}

int			main(int argc, char **argv)
{
	t_libx		libx;
	t_matrix	matrix;
	t_prog		prog;
	t_color		color;

	color = create_color(80, 0.82, 0.59);
	if (argc != 2 || !ft_strcmp(argv[1], "/dev/zero") ||
		!tab_of_points(argv[1], &matrix))
	{
		ft_putstr("error with map\n");
		return (1);
	}
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, SIZE_X, SIZE_Y, "fdf");
	libx.img = &(t_img){mlx_new_image(libx.mlx, SIZE_X, SIZE_Y)};
	libx.img->data = (int*)mlx_get_data_addr(
		libx.img->ptr, &(libx.img->bpp), &(libx.img->sl), &(libx.img->endian));
	prog = (t_prog){&libx, &matrix, color};
	draw(&matrix, color, &libx);
	mlx_put_image_to_window(libx.mlx, libx.win, libx.img->ptr, 0, 0);
	mlx_hook(libx.win, 2, 3, transform, &prog);
	mlx_loop(libx.mlx);
	free_matrix(&matrix);
	return (0);
}
