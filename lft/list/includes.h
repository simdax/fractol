/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:25:48 by simdax            #+#    #+#             */
/*   Updated: 2018/01/08 17:56:35 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_INCLUDES_H
# define MERGE_INCLUDES_H

# include "../libft.h"

int	ft_lstgetmax(t_list *list, int val,
                      int (*f)(t_list *el, int val));
t_list	*ft_lstsort(t_list *list, int (*cmp)(t_list*, t_list*));
int	ft_cmp_strlen(t_list *one, t_list *two);
int	ft_cmp_str(t_list *one, t_list *two);
int	ft_cmp_size(t_list *one, t_list *two);
void	ft_lstprint(t_list *el);

#endif
