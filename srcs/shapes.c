/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:49:25 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/19 10:09:36 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float 	ft_abs(float a)
{
	return (a < 0 ? -a : a);
}

void	draw_line(t_line line, int reverse, t_color color, t_libx *libx)
{
	float x;
	float y;
	float z_slope;
	float z1;
	float z2;
	
	y = 0;
	x = 0;
	z1 = line.origin.z * 5;
	z2 = line.goal.z * 5;
	z_slope = (z2 - z1) * 0.02;
	while (x != line.steps)
	{
		if (reverse)
			mlx_pixel_put(libx->mlx, libx->win,
						line.origin.x + y, line.origin.y + x,
						  color2hex(update(color, z1 + (x * z_slope), 0, 0)));
		else
			mlx_pixel_put(libx->mlx, libx->win,
						line.origin.x + x, line.origin.y + y,
						  color2hex(update(color, z2 + (x * z_slope), 0, 0)));
		x += line.steps > 0 ? 1 : -1;
		y += line.slope;
	}
}

void	line(t_point x1, t_point x2, t_color color, t_libx *libx)
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
