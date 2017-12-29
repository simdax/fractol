/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:14:03 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/28 20:30:06 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translateX(t_point *points, int of, int len)
{
	while (--len >= 0)
		points[len].x += of;
}

void	translateY(t_point *points, int of, int len)
{
	while (--len >= 0)
		points[len].y += of;
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
	float		tmpx;
	float	 	tmpy;
	int			len;
	t_point		*points;

	len = matrix->len;
	while (--len >= 0)
	{
		tmpx = matrix->points[len].x - origin.x;
		tmpy = matrix->points[len].y - origin.y;
		matrix->points[len].x = tmpx * cos(angle) - tmpy * sin(angle) + origin.x;
		matrix->points[len].y = tmpy * cos(angle) + tmpx * sin(angle) + origin.y;
	}
}

void	event_manager(int keycode, t_matrix *matrix)
{
	/* if (keycode == 46) */
	/* 	translate(matrix->points, 1, len); */
	if (keycode == 124)
		rotate(matrix, 20, (t_point){100, 100, 0});
	else if (keycode == 46)
		scale(matrix, 1.5);
	else if (keycode == 47)
		exit(1);
}
