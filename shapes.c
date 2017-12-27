/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:49:25 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/27 14:52:10 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	square(int x, int y, int width, t_libx *libx)
{
	int tmp;
	int tmp2;

	tmp = 0;
	while (tmp < width)
	{
		tmp2 = 0;
		while (tmp2 < width)
		{
			PUT(y + tmp2, x + tmp);
			++tmp2;
		}
		++tmp;
	}			
}

static void draw_line(t_point point, float slope, int steps, t_libx *libx)
{	
	float x;
	float y;	
	
	x = 0;
	y = 0;
	if (!steps)
	{
		while ((int)y != slope)
		{
			PUT(point.x, point.y + (int)y);
			y += slope > 0 ? 1 : -1;
		}
	}
	else {
		while ((int)x != steps)
		{
			PUT(point.x + (int)x, point.y + (int)y);
			x += steps > 0 ? 1 : -1;
			y += slope;
		}
	}
}

void	line(t_point x1, t_point x2, t_libx *libx)
{
	int stepsX;
	int stepsY;
	float slope;
	
	stepsX = x2.x - x1.x;
	stepsY = x2.y - x1.y;
	if (!stepsX)
	{
		if (!stepsY)
		{
			PUT(x1.x, x1.y);
			return ;
		}	
		draw_line(x1, stepsY, 0, libx);
	}
	slope = (float)stepsY / (float)stepsX;
	slope = slope < 0 ? -slope : slope;
	if (slope <= 1)
		draw_line(x1, slope * (stepsY < 0 ? -1 : 1), stepsX, libx);
	else
		line(x2, x1, libx);
}
