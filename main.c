/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/27 12:49:12 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
