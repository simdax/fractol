/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 17:53:22 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/31 18:12:39 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			burningship(int n, double c_re, double c_im, t_flags *flags)
{
	double		z_re;
	double		z_im;
	double		z_re2;
	double		z_im2;

	z_re = c_re;
	z_im = c_im;
	while (n--)
	{
		z_re2 = z_re * z_re;
		z_im2 = z_im * z_im;
		if (z_re2 + z_im2 > 4)
			return (0);
		z_im = 2 * ft_abs_d(z_re) * ft_abs_d(z_im) + c_im;
		z_re = z_re2 - z_im2 + c_re;
	}
	return (color2hex(create_color(flags->color1, z_re2, z_im2)));
}

int			julia(int n, double c_re, double c_im, t_flags *flags)
{
	double		z_re;
	double		z_im;
	double		z_re2;
	double		z_im2;

	z_re = c_re;
	z_im = c_im;
	while (n--)
	{
		z_re2 = z_re * z_re;
		z_im2 = z_im * z_im;
		if (z_re2 + z_im2 > 4)
		{
			return (color2hex(create_color(z_re2 * z_im2 * flags->color1, 0.3,
										0.3)));
		}
		z_im = 2 * z_re * z_im + flags->y;
		z_re = z_re2 - z_im2 + flags->x;
	}
	return (color2hex(create_color(z_re2 * z_im2 * flags->color1, 0.3, 0.3)));
}

int			julia2(int n, double c_re, double c_im, t_flags *flags)
{
	double		z_re;
	double		z_im;
	double		z_re2;
	double		z_im2;

	z_re = c_re;
	z_im = -c_im;
	while (n--)
	{
		z_re2 = z_re * z_re;
		z_im2 = z_im * z_im;
		if (z_re2 + z_im2 > 4)
			return (color2hex(create_color(flags->color1, 0.2, 0.58)));
		z_im = 2 * z_re * -z_im + flags->y;
		z_re = z_re2 - z_im2 + flags->x;
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
