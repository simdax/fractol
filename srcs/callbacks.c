/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:15:13 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/31 14:58:11 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_move(int x, int y, t_prog *prog)
{
	if (prog->set->f == julia)
	{
		prog->flags->x = (double)50 / x;
		prog->flags->y = (double)50 / y;
		draw(prog);
	}
	return (0);
}

int		clos(void *d)
{
	write(1, "bisous :* \n", 11);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_prog *prog)
{
	double		spanx;
	double		spany;
	double		xx;
	double		yy;

	spanx = (prog->set->max_re - prog->set->min_re);
	spany = (prog->set->max_im - prog->set->min_im);
	xx = (x / (double)(SIZE_X / 2) - 1) * spanx / 2;
	yy = -(y / (double)(SIZE_Y / 2) - 1) * spany / 2;
	prog->set->min_re += xx / 3;
	prog->set->max_re += xx / 3;
	prog->set->min_im += yy / 3;
	prog->set->max_im += yy / 3;
	prog->set->re_factor = spanx / (SIZE_X - 1);
	prog->set->im_factor = spany / (SIZE_Y - 1);
	draw(prog);
	prog->set->min_re += spanx / 20;
	prog->set->max_re -= spanx / 20;
	prog->set->min_im += spany / 20;
	prog->set->max_im -= spany / 20;
	prog->set->max_iterations += 0.25;
	return (0);
}

void	go_f(int (*f)(int, double, double, t_flags*), t_prog *prog)
{
	prog->set->f = f;
	init_set(prog->set);
}

void	mvt(int keycode, t_prog *prog)
{
	double		spanx;
	double		spany;
	double		xx;
	double		yy;
	
	spanx = (prog->set->max_re - prog->set->min_re);
	spany = (prog->set->max_im - prog->set->min_im);
	if (keycode == 123 || keycode == 124)
	{
		xx = (keycode == 123 ? -spanx : spanx) / 10;
		prog->set->min_re += xx;
		prog->set->max_re += xx;
	}
	if (keycode == 125 || keycode == 126)
	{
		yy = (keycode == 125 ? -spany : spany) / 10;
		prog->set->min_im += yy;
		prog->set->max_im += yy;
	}
}

int		keyb_hook(int keycode, t_prog *prog)
{
	printf("key %d\n", keycode); fflush(stdout);
	if (keycode == A)
		go_f(mandelbrot, prog);
	else if (keycode == S)
		go_f(julia, prog);
	else if (keycode == D)
		go_f(burningship, prog);
	else if (keycode == Q)
		prog->flags->color1 += 20;
	else if (keycode == W)
		prog->flags->color1 -= 20;
	else if (keycode == E)
		prog->flags->color2 += 20;
	else if (keycode == R)
		prog->flags->color2 -= 20;
	else
		mvt(keycode, prog);
	draw(prog);
	if (keycode == 53)
		exit(0);
	return (0);
}
