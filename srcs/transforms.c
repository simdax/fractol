/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:14:03 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/19 11:21:24 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_matrix *matrix, int x, int y)
{
	int len;

	len = matrix->len;
	while (--len >= 0)
	{
		matrix->points[len].x += x;
		matrix->points[len].y += y;
	}
}

void	scale(t_matrix *matrix, float factor)
{
	int len;

	len = matrix->len;
	while (--len >= 0)
	{
		matrix->points[len].x *= factor;
		matrix->points[len].y *= factor;
	}
}

void	rotate(t_matrix *matrix, float angle, t_point origin)
{
	double		tmpx;
	double		tmpy;
	int			len;

	len = matrix->len;
	while (--len >= 0)
	{
		tmpx = origin.x - matrix->points[len].x;
		tmpy = origin.y - matrix->points[len].y;
		matrix->points[len].x =
			tmpx * cos(angle) - tmpy * sin(angle) + origin.x;
		matrix->points[len].y =
			tmpy * cos(angle) + tmpx * sin(angle) + origin.y;
	}
}

void	event_manager(int keycode, t_matrix *matrix)
{
	if (keycode == 123)
		rotate(matrix, M_PI / 4, (t_point){SIZE_X / 2, SIZE_Y / 2, 0});
	else if (keycode == 124)
		rotate(matrix, M_PI / -4, (t_point){SIZE_X / 2, SIZE_Y / 2, 0});
	else if (keycode == 126)
	{
		scale(matrix, 1.25);
		translate(matrix, SIZE_X / -8, SIZE_Y / -8);
	}
	else if (keycode == 125)
	{
		scale(matrix, 0.75);
		translate(matrix, SIZE_X / 8, SIZE_Y / 8);
	}
	else if (keycode == 53)
		exit(0);
}
