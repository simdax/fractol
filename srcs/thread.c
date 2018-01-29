/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:40:56 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/29 14:03:49 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

pthread_cond_t condition = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

int	parallelize(t_fractal *set, int *data)
{
	pthread_t thread_one;
	pthread_t thread_two;
	pthread_t thread_three;
	pthread_t thread_four;

	pthread_create (&thread_one, NULL, calc_set, &(t_thread){set, data, 0, SIZE_Y / 4});
	pthread_create (&thread_two, NULL, calc_set, &(t_thread){set, data, SIZE_Y / 4 + 1, SIZE_Y / 2});
	pthread_create (&thread_three, NULL, calc_set, &(t_thread){set, data, SIZE_Y / 2 + 1, SIZE_Y * 3 / 4});
	pthread_create (&thread_four, NULL, calc_set, &(t_thread){set, data, (SIZE_Y * 3 / 4) + 1, SIZE_Y});
	pthread_join (thread_one, NULL);
	pthread_join (thread_two, NULL); /* Attente de la fin des threads */
	pthread_join (thread_three, NULL);
	pthread_join (thread_four, NULL); /* Attente de la fin des threads */
	return (1);
}
