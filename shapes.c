/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:49:25 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/28 12:10:53 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* void	square(int x, int y, int width, t_libx *libx) */
/* { */
/* 	int tmp; */
/* 	int tmp2; */

/* 	tmp = 0; */
/* 	while (tmp < width) */
/* 	{ */
/* 		tmp2 = 0; */
/* 		while (tmp2 < width) */
/* 		{ */
/* 			PUT(y + tmp2, x + tmp); */
/* 			++tmp2; */
/* 		} */
/* 		++tmp; */
/* 	} */
/* } */

void	draw_line(t_line line, int reverse, long color, t_libx *libx)
{
	float x;
	float y;

	y = 0;
	x = 0;
	while ((int)x != line.steps)
	{
		if (reverse)
		{
			PUT(line.origin.x + (int)y, line.origin.y + (int)x, color);
		}
		else
			PUT(line.origin.x + (int)x, line.origin.y + (int)y, color);
		x += line.steps > 0 ? 1 : -1;
		y += line.slope;
	}
}

void	line(t_point x1, t_point x2, long color, t_libx *libx)
{
	int		steps_x;
	int		steps_y;
	float	slope;

	steps_x = x2.x - x1.x;
	steps_y = x2.y - x1.y;
	slope = (float)steps_y / (float)steps_x;
	slope = slope < 0 ? -slope : slope;
	if (slope <= 1)
		draw_line((t_line){
				x1,
				slope * (steps_y < 0 ? -1 : 1),
				steps_x
					}, 0, color, libx);
	else
		draw_line((t_line){
				x1,
					1 / slope * (steps_x < 0 ? -1 : 1),
						steps_y
					}, 1, color, libx);
}
