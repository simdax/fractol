/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:40:56 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/29 17:37:15 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int balance_du_gros_thread(t_fractal *set, int *data, int threads_nb)
{
	pthread_t	*threads;
	t_thread	*io;
	int			i;
	int			u;

	if (!(threads = malloc(sizeof(pthread_t) * threads_nb)))
		return (0);
	if (!(io = malloc(sizeof(t_thread) * threads_nb)))
		return (0);
	i = 0;
	while (i < threads_nb)
	{
//		ft_memcpy(&io[i], &(t_thread){set, data, (SIZE_Y * i) / threads, (SIZE_Y * (i + 1)) / threads, i}, sizeof(t_thread));
		io[i] = (t_thread){set, data, (SIZE_Y * i) / threads_nb, (SIZE_Y * (i + 1)) / threads_nb, i};
		u = pthread_create(&threads[i], NULL, calc_set, &io[i]);
		++i;
	}
	i = 0;
	while (i < threads_nb)
	{
		pthread_join(threads[i], NULL);
		++i;
	}
	free(threads);
	free(io);
	return (1);
}
