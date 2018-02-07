/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:26:59 by scornaz           #+#    #+#             */
/*   Updated: 2018/02/07 18:15:49 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_hook(int button, int x, int y, t_prog *prog)
{
	if (button == 4 && prog->set->max_re < 5)
		mouse_hook_r(x, y, prog);
	else if (button == 5)
		mouse_hook_l(x, y, prog);
	return (0);
}

void	zoom_chelou(double xx, double yy, t_prog *prog)
{
	if ((xx > 0 && yy < 0) || (xx < 0 && yy > 0))
	{
		xx = -xx;
		yy = -yy;
	}
	prog->set->min_re += yy / 10;
	prog->set->max_re += yy / 10;
	prog->set->min_im += xx / 10;
	prog->set->max_im += xx / 10;
}

int		mouse_hook_r(int x, int y, t_prog *prog)
{
	double		spanx;
	double		spany;
	double		xx;
	double		yy;

	spanx = (prog->set->max_re - prog->set->min_re);
	spany = (prog->set->max_im - prog->set->min_im);
	xx = (x / (double)(SIZE_X / 2) - 1) * spanx / 2;
	yy = -(y / (double)(SIZE_Y / 2) - 1) * spany / 2;
	zoom_chelou(xx, yy, prog);
	prog->set->re_factor = spanx / (SIZE_X - 1);
	prog->set->im_factor = spany / (SIZE_Y - 1);
	draw(prog);
	prog->set->min_re -= spanx / 20;
	prog->set->max_re += spanx / 20;
	prog->set->min_im -= spany / 20;
	prog->set->max_im += spany / 20;
	prog->set->max_iterations -= 0.35;
	return (0);
}

int		mouse_hook_l(int x, int y, t_prog *prog)
{
	double		spanx;
	double		spany;
	double		xx;
	double		yy;

	spanx = (prog->set->max_re - prog->set->min_re);
	spany = (prog->set->max_im - prog->set->min_im);
	xx = (x / (double)(SIZE_X / 2) - 1) * spanx / 2;
	yy = -(y / (double)(SIZE_Y / 2) - 1) * spany / 2;
	prog->set->min_re += xx / 5;
	prog->set->max_re += xx / 5;
	prog->set->min_im += yy / 5;
	prog->set->max_im += yy / 5;
	prog->set->re_factor = spanx / (SIZE_X - 1);
	prog->set->im_factor = spany / (SIZE_Y - 1);
	draw(prog);
	prog->set->min_re += spanx / 20;
	prog->set->max_re -= spanx / 20;
	prog->set->min_im += spany / 20;
	prog->set->max_im -= spany / 20;
	prog->set->max_iterations += 0.35;
	return (0);
}

int		close_win(t_prog *prog)
{
	--g_wins;
	if (!g_wins)
	{
		write(1, "BISOUS ❤️ \n", 15);
		exit(0);
	}
	free(prog->libx->img);
	free(prog->flags);
	return (0);
}
