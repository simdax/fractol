/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:14:03 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/28 14:57:35 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* typedef struct	s_ops */
/* { */
/* 	int			keycode; */
/* 	void		(*transform)(t_point*, int); */
/* }				t_ops; */

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

void	scale(t_point *points, int len)
{
	while (--len >= 0)
		points[len].x += 10;
}

void	rotate(t_point *points, float angle, int len)
{
	float		tmpx;
	float	 	tmpy;
	
	while (--len >= 0)
	{
		tmpx = points[len].x * cos(angle) - points[len].y * sin(angle);
		tmpy = points[len].y * cos(angle) + points[len].x * sin(angle);
		points[len].x = tmpx;
		points[len].y = tmpy;
	}
}

int		transform(int keycode, void *arg)
{
	t_prog			*prog;
	int 			len;

	printf("keycode %d\n", keycode);
	fflush(stdout);
	prog =	(t_prog*)arg;
	len = prog->matrix->len;
	draw(prog->matrix, 0x000000, prog->libx);
	/* if (keycode == 46) */
	/* 	translate(prog->matrix->points, 1, len); */
	if (keycode == 124)
	{
		translateX(prog->matrix->points, 50, len);
		translateY(prog->matrix->points, -10, len);
		rotate(prog->matrix->points, 0.13, len);
	}
	else if (keycode == 46)
		scale(prog->matrix->points, len);
	draw(prog->matrix, 0x00FF00, prog->libx);
	return (0);
}

