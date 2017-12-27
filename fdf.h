/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:48:31 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/27 12:50:50 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h" 
# include "math.h"
# include "stdio.h"

# define PUT(x, y)	mlx_pixel_put(libx->mlx, libx->win, x, y, 0x00FFFFFF);
# define ABS(x)		x < 0 ? -x : x
# define MAX(x, y)	x > y ? x : y

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

#endif
