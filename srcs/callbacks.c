/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:15:13 by scornaz           #+#    #+#             */
/*   Updated: 2018/02/01 09:45:11 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_move(int x, int y, t_prog *prog)
{
	if (prog->set->f == julia || prog->set->f == julia2)
	{
		prog->flags->x = (double)50 / x;
		prog->flags->y = (double)50 / y;
		draw(prog);
	}
	return (0);
}

void	go_f(int (*f)(int, double, double, t_flags*), t_prog *prog)
{
	ft_bzero(prog->libx->img->data, SIZE_X * SIZE_Y + 1);
	mlx_put_image_to_window(prog->libx->mlx, prog->libx->win,
							prog->libx->img->ptr, 0, 0);
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
	if (keycode == A)
		go_f(mandelbrot, prog);
	else if (keycode == S)
		go_f(julia, prog);
	else if (keycode == D)
		go_f(mandelbrot2, prog);
	else if (keycode == F)
		go_f(julia2, prog);
	else if (keycode == G)
		go_f(burningship, prog);
	else if (keycode == Z)
		prog->flags->factor += 0.1;
	else if (keycode == X)
		prog->flags->factor -= 0.1;
	else if (keycode == C)
		prog->flags->color1 += 20;
	else if (keycode == V)
		prog->flags->color1 -= 20;
	else
		mvt(keycode, prog);
	draw(prog);
	if (keycode == 53)
		exit(0);
	return (0);
}
