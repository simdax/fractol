/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetmax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:45:36 by simdax            #+#    #+#             */
/*   Updated: 2018/01/08 17:58:00 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	ft_lstgetmax(t_list *list, int val,
                      int (*f)(t_list *el, int val))
{
	while (list)
	{
          val = f(list, val);
		list = list->next;
	}
        return (val);
}
