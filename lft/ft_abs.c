/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:39:09 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/30 18:54:06 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_abs(int value)
{
	return (value < 0 ? -value : value);
}

double	ft_abs_d(double value)
{
	return (value < 0 ? -value : value);
}

int		ft_notneg(int value)
{
	return (value < 0 ? 0 : value);
}
