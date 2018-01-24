/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 20:59:02 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/24 17:38:36 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	ft_abs(float a)
{
	return (a < 0 ? -a : a);
}

void			fill_img_pixel(int *img, int color, int x, int y)
{
	if (x > 0 && x < SIZE_X && y > 0 && y < SIZE_Y)
		img[y * SIZE_X + x] = color;
}

void			draw_line(t_line line, int reverse, t_color color, t_libx *libx)
{
	t_rien	args;

	args = (t_rien){0, 0, line.origin.z * 5, line.goal.z * 5};
	args.z_slope = (args.z2 - args.z1) * (1 / (float)line.steps);
	while (args.x != line.steps)
	{
		if (reverse)
			fill_img_pixel(libx->img->data,
						color2hex(update(color, args.z1
											+ (args.x * args.z_slope), 0, 0)),
						line.origin.x + args.y, line.origin.y + args.x);
		else
			fill_img_pixel(libx->img->data,
						color2hex(update(color, args.z1
											+ (args.x * args.z_slope), 0, 0)),
						line.origin.x + args.x, line.origin.y + args.y);
		args.x += line.steps > 0 ? 1 : -1;
		args.y += line.slope;
	}
}

void			line(t_point x1, t_point x2, t_color color, t_libx *libx)
{
	int		steps_x;
	int		steps_y;
	float	slope;
	float	z_slope;

	steps_x = x2.x - x1.x;
	steps_y = x2.y - x1.y;
	slope = (float)steps_y / (float)steps_x;
	slope = slope < 0 ? -slope : slope;
	if (slope <= 1)
		draw_line((t_line){
				x1,
				slope * (steps_y < 0 ? -1 : 1),
					steps_x, x2
					}, 0, color, libx);
	else
		draw_line((t_line){
				x1,
					1 / slope * (steps_x < 0 ? -1 : 1),
					steps_y, x2
					}, 1, color, libx);
}
