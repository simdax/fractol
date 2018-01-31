/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:40:56 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/31 17:40:36 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	balance_du_gros_thread(t_fractal *set, int *data, t_flags *flags)
{
	pthread_t	*threads;
	t_thread	*io;
	int			i;
	int			u;

	if (!(threads = malloc(sizeof(pthread_t) * flags->iterations)))
		return (0);
	if (!(io = malloc(sizeof(t_thread) * flags->iterations)))
		return (0);
	i = 0;
	while (i < flags->iterations)
	{
		io[i] = (t_thread){set, data, (SIZE_Y * i) / flags->iterations,
						(SIZE_Y * (i + 1)) / flags->iterations, i, flags};
		u = pthread_create(&threads[i], NULL, calc_set, &io[i]);
		++i;
	}
	i = 0;
	while (i < flags->iterations)
		pthread_join(threads[i++], NULL);
	free(threads);
	free(io);
	return (1);
}
