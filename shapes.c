/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:49:25 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/29 15:03:47 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_line line, int reverse, long color, t_libx *libx)
{
	float x;
	float y;

	y = 0;
	x = 0;
	while (x != line.steps)
	{
		if (reverse)
			mlx_pixel_put(libx->mlx, libx->win,
						line.origin.x + y, line.origin.y + x,
						color);
		else
			mlx_pixel_put(libx->mlx, libx->win,
						line.origin.x + x, line.origin.y + y,
						color);
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
