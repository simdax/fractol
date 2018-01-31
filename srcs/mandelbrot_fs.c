/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_fs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:33:53 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/31 17:41:22 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		mandelbrot(int n, double c_re, double c_im, t_flags *flags)
{
	double		z_re;
	double		z_im;
	double		z_re2;
	double		z_im2;
	double		i;

	z_re = c_re;
	z_im = c_im;
	i = 1;
	while (n--)
	{
		z_re2 = z_re * z_re;
		z_im2 = z_im * z_im;
		if (z_re2 + z_im2 > 4)
			++i;
		z_im = 2 * z_re * z_im + c_im;
		z_re = z_re2 - z_im2 + c_re;
	}
	return (i * 1560);
}

int		mandelbrot2(int n, double c_re, double c_im, t_flags *flags)
{
	double		z_re;
	double		z_im;
	double		z_re2;
	double		z_im2;
	double		i;

	z_re = c_re;
	z_im = -c_im;
	i = 1;
	while (n--)
	{
		z_re2 = z_re * z_re;
		z_im2 = z_im * z_im;
		if (z_re2 + z_im2 > 4)
			++i;
		z_im = 2 * z_re * -z_im - c_im;
		z_re = z_re2 - z_im2 + c_re;
	}
	return (i * 1560);
}
