/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:14:03 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/29 14:41:36 by scornaz          ###   ########.fr       */
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
	float		tmpx;
	float		tmpy;
	int			len;

	len = matrix->len;
	while (--len >= 0)
	{
		tmpx = matrix->points[len].x - origin.x;
		tmpy = matrix->points[len].y - origin.y;
		matrix->points[len].x =
			tmpx * cos(angle) - tmpy * sin(angle) + origin.x;
		matrix->points[len].y =
			tmpy * cos(angle) + tmpx * sin(angle) + origin.y;
	}
}

void	event_manager(int keycode, t_matrix *matrix)
{
	if (keycode == 82)
		rotate(matrix, 18, (t_point){SIZE_X / 2, SIZE_Y / 2, 0});
	else if (keycode == 126)
		scale(matrix, 1.5);
	else if (keycode == 124)
		translate(matrix, -10, 0);
	else if (keycode == 125)
		scale(matrix, 0.75);
	else if (keycode == 123)
		translate(matrix, 10, 0);
	else if (keycode == 53)
		exit(0);
}
