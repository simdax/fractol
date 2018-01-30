/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:15:13 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/30 18:31:30 by scornaz          ###   ########.fr       */
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
	prog->set->max_iterations += 2;
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
	if (keycode == 0)
		go_f(mandelbrot, prog);
	else if (keycode == 1)
		go_f(julia, prog);
	else if (keycode == 2)
		prog->flags->color1 += 10;
	else if (keycode == 3)
		prog->flags->color1 -= 10;
	else if (keycode == 4)
		prog->flags->color2 += 10;
	else if (keycode == 5)
		prog->flags->color2 -= 10;
	else
		mvt(keycode, prog);
	draw(prog);
	if (keycode == 53)
		exit(0);
	return (0);
}
