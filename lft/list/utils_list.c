/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:58:00 by simdax            #+#    #+#             */
/*   Updated: 2018/01/08 15:04:27 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "includes.h"

void	ft_lstprint(t_list *el)
{
  write(1, el->content, ft_strlen(el->content));
  write(1, " ", 1);
}
