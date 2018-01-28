/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:53:22 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/28 20:05:59 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <unistd.h>

/* inline void	hydrate_set(t_fractal *set) */
/* { */
/* 	prog->set->max_im = prog->set->min_im + (prog->set->max_re - prog->set->min_re) * */
/* 		SIZE_Y / SIZE_X; */
/* } */

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
			return (0x00FF0450);//color2hex(create_color(Z_re2, Z_re2, Z_im2)));
		Z_im = 2 * Z_re * Z_im + c_im;
		Z_re = Z_re2 - Z_im2 + c_re;
	}
	return (0);
//	return (color2hex(create_color(240, Z_re2, Z_im2)));
//	return (Z_re2 + Z_im2 * 456121);
}

void		calc_set(t_fractal *set, int *buf)
{
	double c_im;
	double c_re;
	unsigned x;
	unsigned y;

	y = 0;
	while (y < SIZE_Y)
	{
		c_im = set->max_im - y * set->im_factor;
		x = 0;
		while (x < SIZE_X)
		{
			c_re = set->min_re + x * set->re_factor;
			buf[y * SIZE_X + x] = mandelbrot(set->max_iterations, c_re, c_im);
			++x;
		}
		++y;
	}
}
