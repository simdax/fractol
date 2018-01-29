/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/29 19:49:49 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		init_set(t_fractal *set, t_prog *prog);

void	go_f(int (*f)(int, double, double, t_flags*), t_prog *prog)
{
	prog->set->f = f;
	init_set(prog->set, prog);
}

int		keyb_hook(int keycode, void *data)
{
	t_prog	*prog;

	prog = data;
	if (keycode == 0)
		go_f(mandelbrot, prog);
	else if (keycode == 1)
		go_f(julia, prog);
	else if (keycode == 2)
	{
		prog->color += 10;
		if ((balance_du_gros_thread(prog->set, prog->libx->img->data,
									&(t_flags){0, 0, prog->set->max_iterations, prog->color})))
			mlx_put_image_to_window(prog->libx->mlx, prog->libx->win,
									prog->libx->img->ptr, 0, 0);
	}
	else if (keycode == 3)
		prog->color -= 10;
	else if (keycode == 53)
		exit(0);
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
	if ((balance_du_gros_thread(prog->set, prog->libx->img->data,
			&(t_flags){xx, yy, prog->set->max_iterations, prog->color})))
		mlx_put_image_to_window(prog->libx->mlx, prog->libx->win,
								prog->libx->img->ptr, 0, 0);
	else
		exit(0);
	prog->set->min_re += spanx / 10;
	prog->set->max_re -= spanx / 10;
	prog->set->min_im += spany / 10;
	prog->set->max_im -= spany / 10;
	prog->set->max_iterations += 2;
	return (0);
}

void		take_flags(int argc, char **argv, t_fractal *set)
{
	//
}

void		init_set(t_fractal *set, t_prog *prog)
{
	set->max_re = 1.0;
	set->min_re = -1.0;
	set->max_im = 1.0;
	set->min_im = -1.0;
	set->max_iterations = 10;
	set->re_factor = (set->max_re - set->min_re) / (SIZE_X - 1);
	set->im_factor = (set->max_im - set->min_im) / (SIZE_Y - 1);
	balance_du_gros_thread(set, prog->libx->img->data,
						   &(t_flags){0, 0, set->max_iterations, 40});
	mlx_put_image_to_window(prog->libx->mlx, prog->libx->win, prog->libx->img->ptr, 0, 0);
	return ;
}

int			main(int argc, char **argv)
{
	t_libx		libx;
	t_prog		prog;
	t_fractal	set;
	
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, SIZE_X, SIZE_Y, "fractol");
	libx.img = &(t_img){mlx_new_image(libx.mlx, SIZE_X, SIZE_Y)};
	libx.img->data = (int*)mlx_get_data_addr(
		libx.img->ptr, &(libx.img->bpp), &(libx.img->sl), &(libx.img->endian));
	set.f = julia;
	prog = (t_prog){&libx, 0, &set, 40};
	init_set(&set, &prog);
	mlx_hook(libx.win, 4, 4, mouse_hook, &prog);
	mlx_hook(libx.win, 2, 3, keyb_hook, &prog);
	mlx_loop(libx.mlx);
	return (0);
}
