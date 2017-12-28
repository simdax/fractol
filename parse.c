/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:51:57 by scornaz           #+#    #+#             */
/*   Updated: 2017/12/28 15:52:04 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

/* void	parse() */
/* { */
/* 	int fd; */

/* 	fd = open(""); */
/* } */

t_point	point_from_index(int nb, int space, int rows, int cols)
{
	return ((t_point){
			OFFSET_X + space * (nb % rows),
			OFFSET_Y + space * (nb / cols),
			0});
}

t_point	*tab_of_points(int nb, int space, int rows, int cols)
{
	t_point *res;

	res = (t_point*)malloc(sizeof(t_point) * nb);
	while (--nb >= 0)
		res[nb] = point_from_index(nb, space, rows, cols);
	return (res);
}
