/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:30:02 by scornaz           #+#    #+#             */
/*   Updated: 2017/11/09 18:24:47 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*cpy;

	cpy = dst;
	while (len-- && *src)
		*cpy++ = *src++;
	if (++len)
		while (len--)
			*cpy++ = '\0';
	return (dst);
}
