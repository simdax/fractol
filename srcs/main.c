/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/29 17:39:06 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keyb_hook(int keycode, void *data)
{
	event_manager(keycode, ((t_prog*)data)->matrix);
	return (0);
}


int		mouse_hook(int button, int x, int y, void *data)
{
	t_prog		*prog;
	double		spanx;
	double		spany;
	double		xx;
	double		yy;

	prog = data;
	spanx = (prog->set->max_re - prog->set->min_re);
	spany = (prog->set->max_im - prog->set->min_im);
	xx = (x / (double)(SIZE_X / 2) - 1) * spanx / 2;
	yy = -(y / (double)(SIZE_Y / 2) - 1) * spany / 2;
	prog->set->min_re += xx;
	prog->set->max_re += xx;
	prog->set->min_im += yy;
	prog->set->max_im += yy;
	prog->set->re_factor = spanx / (SIZE_X - 1);
	prog->set->im_factor = spany / (SIZE_Y - 1);
	if ((balance_du_gros_thread(prog->set, prog->libx->img->data, prog->set->max_iterations)))
		mlx_put_image_to_window(prog->libx->mlx, prog->libx->win,
								prog->libx->img->ptr, 0, 0);
	prog->set->min_re += spanx / 10;
	prog->set->max_re -= spanx / 10;
	prog->set->min_im += spany / 10;
	prog->set->max_im -= spany / 10;
	prog->set->max_iterations += 2;
	return(0);
}

void		take_flags(int argc, char **argv, t_fractal *set)
{
	/* set->min_re = argc > 1? parse(argv[1]) : -1.0; */
	/* set->max_re = argc > 1? parse(argv[1]) : -1.0; */
	/* set->min_im = argc > 1? parse(argv[1]) : -1.0; */
	/* set->min_re = argc > 1? parse(argv[1]) : -1.0; */
	set->max_re = 1.0;
	set->min_re = -1.0;
	set->max_im = 1.0;
	set->min_im = -1.0;
	set->max_iterations = 50;
	set->re_factor = (set->max_re - set->min_re) / (SIZE_X - 1);
	set->im_factor = (set->max_im - set->min_im) / (SIZE_Y - 1);
	return ;
}

int			main(int argc, char **argv)
{
	t_libx		libx;
	t_prog		prog;
	t_fractal	set;
	
	take_flags(argc, argv, &set);
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, SIZE_X, SIZE_Y, "fractol");
	libx.img = &(t_img){mlx_new_image(libx.mlx, SIZE_X, SIZE_Y)};
	libx.img->data = (int*)mlx_get_data_addr(
		libx.img->ptr, &(libx.img->bpp), &(libx.img->sl), &(libx.img->endian));
	prog = (t_prog){&libx, 0, &set};
	balance_du_gros_thread(&set, libx.img->data, 50);
	mlx_put_image_to_window(libx.mlx, libx.win, libx.img->ptr, 0, 0);
	mlx_hook(libx.win, 4, 4, mouse_hook, &prog);
	mlx_hook(libx.win, 2, 3, keyb_hook, &prog);
	mlx_loop(libx.mlx);
	return (0);
}
