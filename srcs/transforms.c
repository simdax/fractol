/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:14:03 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/20 17:55:22 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_matrix *matrix, int x, int y)
{
	int len;

	len = matrix->map->len;
	while (--len >= 0)
	{
		matrix->points[len].x += x;
		matrix->points[len].y += y;
	}
}

void	scale(t_matrix *matrix, float factor)
{
	int len;

	len = matrix->map->len;
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

	len = matrix->map->len;
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

void	change_proj(t_matrix *matrix, float c1, float c2)
{
	int		nb;
	t_point *res;

	nb = matrix->map->len;
	res = (t_point*)malloc(sizeof(t_point) * nb);
	matrix->c1 += c1;
	matrix->c2 += c2;
	if (matrix->c1 <= 0)
		matrix->c1 = 0.1;
	if (matrix->c2 <= 0)
		matrix->c2 = 0.1;
	while (--nb >= 0)
		res[nb] = projection(nb, matrix);
	free(matrix->points);
	matrix->points = res;
	center_matrix(matrix);
}

void	event_manager(int keycode, t_matrix *matrix)
{
	if (keycode == 123)
		rotate(matrix, M_PI / 4, (t_point){SIZE_X / 2, SIZE_Y / 2, 0});
	else if (keycode == 124)
		rotate(matrix, M_PI / -4, (t_point){SIZE_X / 2, SIZE_Y / 2, 0});
	else if (keycode == 126)
		scale(matrix, 1.5);
	else if (keycode == 125)
		scale(matrix, 0.5);
	else if (keycode == 84)
		change_proj(matrix, 0.1, 0);
	else if (keycode == 83)
		change_proj(matrix, 0, 0.1);
	else if (keycode == 86)
		change_proj(matrix, -0.1, 0);
	else if (keycode == 87)
		change_proj(matrix, 0, -0.1);
	else if (keycode == 53)
		exit(0);
}
