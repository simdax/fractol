/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/27 12:45:32 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h" 
#include "math.h"
#include "stdio.h"
#define PUT(x, y)	mlx_pixel_put(libx->mlx, libx->win, x, y, 0x00FFFFFF);
#define ABS(x)		x < 0 ? -x : x
#define MAX(x, y)	x > y ? x : y

typedef struct	s_libx
{
	void		*win;
	void		*mlx;
}				t_libx;
typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;
typedef struct	s_pointf
{
	float		x;
	float		y;
}				t_pointf;

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

static draw_line(t_point point, float slope, int steps, t_libx *libx)
{	
	float x;
	float y;	
	
	x = 0;
	y = 0;
	while ((int)x != steps)
	{
		PUT(point.x + (int)x, point.y + (int)y);
		x += steps > 0 ? 1 : -1;
		y += slope;
	}
}

void	line(t_point x1, t_point x2, t_libx *libx)
{
	int stepsX;
	int stepsY;
	float slope;
	
	stepsX = x2.x - x1.x;
	stepsY = x2.y - x1.y;
	slope = stepsX != 0 ? (float)stepsY / (float)stepsX : 0;
	slope = slope < 0 ? -slope : slope;
	if (slope <= 1)
		draw_line(x1, slope * (stepsY < 0 ? -1 : 1), stepsX, libx);
	else
		line(x2, x1, libx);
}

int		main()
{
	t_libx	libx;
	
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, 400, 400, "fdf");	
	//square(20, 30, 200, &libx);
	t_point depart = {100, 100};
	int amount = 50;
	line(depart, (t_point){depart.x - amount, depart.y + amount}, &libx);
	line(depart, (t_point){depart.x + amount, depart.y + amount}, &libx);
	line(depart, (t_point){depart.x + amount, depart.y - amount}, &libx);
	line(depart, (t_point){depart.x - amount, depart.y - amount}, &libx);

	mlx_loop(libx.mlx);
}
