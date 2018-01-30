/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:15:13 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/30 15:14:55 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_move(int x, int y, void *d)
{
	t_prog	*prog;

	prog = d;
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
	draw(prog);
	prog->set->min_re += spanx / 10;
	prog->set->max_re -= spanx / 10;
	prog->set->min_im += spany / 10;
	prog->set->max_im -= spany / 10;
	prog->set->max_iterations += 2;
	return (0);
}

void	go_f(int (*f)(int, double, double, t_flags*), t_prog *prog)
{
	prog->set->f = f;
	init_set(prog->set);
	draw(prog);
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
		prog->flags->color += 10;
		draw(prog);
	}
	else if (keycode == 3)
	{
		prog->flags->color -= 10;
		draw(prog);		
	}
	else if (keycode == 53)
		exit(0);
	return (0);
}
