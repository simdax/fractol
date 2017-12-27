/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:49:25 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/27 16:36:53 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct	s_line
{
	t_point		origin;
	float		slope;
	int			steps;
}				t_line;

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

static void draw_line(t_line line, int reverse, t_libx *libx)
{	
	float x;
	float y;	
	
	y = 0;
	x = 0;
	while ((int)x != line.steps)
	{
		if (reverse)
		{
			PUT(line.origin.x + (int)y, line.origin.x + (int)x);	
		}
		else
			PUT(line.origin.x + (int)x, line.origin.y + (int)y);
		x += line.steps > 0 ? 1 : -1;
		y += line.slope;
	}
}

void	line(t_point x1, t_point x2, t_libx *libx)
{
	int stepsX;
	int stepsY;
	float slope;
	
	stepsX = x2.x - x1.x;
	stepsY = x2.y - x1.y;
	slope = (float)stepsY / (float)stepsX;
	slope = slope < 0 ? -slope : slope;
	if (slope <= 1)
		draw_line((t_line){
				x1,
				slope * (stepsY < 0 ? -1 : 1),
				stepsX
				}, 0, libx);	
	else
		draw_line((t_line){
				x1,
					1 / slope * (stepsX < 0 ? -1 : 1),
						stepsY
						}, 1, libx);
}
