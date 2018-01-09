/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreduce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:12:40 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/08 17:37:29 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstreduce(t_list *list, void *(*f)(void *a, void *b), void *val)
{
	void *tmp;

	while (list)
	{
		tmp = list->content;
		val = f(val, tmp);
		list = list->next;
	}
        return (val);
}
