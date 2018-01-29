/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:53:22 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/29 16:58:19 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <unistd.h>

int		mandelbrot(int n, double c_re, double c_im)
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
			return (200 * Z_re2 + Z_im2);
//			color2hex(create_color(180, 0.5,0.5));
		Z_im = 2 * Z_re * Z_im + c_im;
		Z_re = Z_re2 - Z_im2 + c_re;
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
			args->data[y * SIZE_X + x] = mandelbrot(args->set->max_iterations, c_re, c_im);
			++x;
		}
		++y;
	}
	printf("je suis fini et je suis %d \n", args->id);
	fflush(stdout);
	pthread_exit(0);
}
