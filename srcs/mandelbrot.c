/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:53:22 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/30 15:15:15 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>
#include <unistd.h>

int		mandelbrot(int n, double c_re, double c_im, t_flags *flags)
{
	double		 Z_re;
	double		 Z_im;
	double		 Z_re2;
	double		 Z_im2;

	Z_re = c_re;
	Z_im = c_im;
	while (n--)
	{
		Z_re2 = Z_re * Z_re;
		Z_im2 = Z_im * Z_im;
		if (Z_re2 + Z_im2 > 2)
			return (color2hex(create_color(Z_re2 * Z_im2 * flags->color, 0.3, 0.3)));
		Z_im = 2 * Z_re * Z_im + c_im;
		Z_re = Z_re2 - Z_im2 + c_re;
	}
	return (0);
}

int		julia(int n, double c_re, double c_im, t_flags *flags)
{
	double		 Z_re;
	double		 Z_im;
	double		 Z_re2;
	double		 Z_im2;

	Z_re = c_re;
	Z_im = c_im;
	while (n--)
	{
		Z_re2 = Z_re * Z_re;
		Z_im2 = Z_im * Z_im;
		if (Z_re2 + Z_im2 > 2)
			return (color2hex(create_color(Z_re2 * Z_im2 * 50, 0.3, 0.3)));
		Z_im = 2 * Z_re * Z_im + flags->y;
		Z_re = Z_re2 - Z_im2 + flags->x;
	}
	return (0);
}

void		*calc_set(void *a)
{
	double		c_im;
	double		c_re;
	unsigned	x;
	unsigned	y;
	t_thread	*args;

	args = a;
	y = args->from;
	while (y < args->to)
	{
		c_im = args->set->max_im - y * args->set->im_factor;
		x = 0;
		while (x < SIZE_X)
		{
			c_re = args->set->min_re + x * args->set->re_factor;
			args->data[y * SIZE_X + x] =
				args->set->f(args->set->max_iterations,
							 c_re, c_im, args->flags);
			++x;
		}
		++y;
	}
	pthread_exit(0);
}
