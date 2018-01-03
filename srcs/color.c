/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:37:00 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/03 18:01:28 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_rgb		hsl2rgb(float hue, float sat, float light)
{
	float c;
	float x;
	float m;
	t_rgb rgb;

	c = (1 - fabs(2 * light - 1)) * sat;
	x = c * (1 - fabs(fmod(hue / 60, 2) - 1));
	m = light - c / 2;
	if (0 <= hue && hue <= 60)
		rgb = (t_rgb){c, x, 0};
	else if (60 <= hue && hue <= 120)
		rgb = (t_rgb){x, c, 0};
	else if (120 <= hue && hue <= 180)
		rgb = (t_rgb){0, c, x};
	else if (180 <= hue && hue <= 240)
		rgb = (t_rgb){0, x, c};
	else if (240 <= hue && hue <= 300)
		rgb = (t_rgb){x, 0, c};
	else if (300 <= hue && hue <= 360)
		rgb = (t_rgb){c, 0, x};
	rgb.r = (rgb.r + m) * 255;
	rgb.g = (rgb.g + m) * 255;
	rgb.b = (rgb.b + m) * 255;
	return (rgb);
}

t_color		create_color(float h, float s, float l)
{
	t_color color;

	color = (t_color){0, 0, 0, 0, 0, 0};
	color.hsl.h = h;
	color.hsl.s = s;
	color.hsl.l = l;
	color.rgb = hsl2rgb(h, s, l);
	return (color);
}

int			color2hex(t_color c)
{
	long res;

	res = (int)c.rgb.r << 16;
	res += (int)c.rgb.g << 8;
	res += (int)c.rgb.b;
	return (res);
}

int			hsl2hex(float h, float s, float l)
{
	return (color2hex(create_color(h, s, l)));
}

t_color		update(t_color c, float h, float s, float l)
{
	c.hsl.h += h;
	c.rgb = hsl2rgb(c.hsl.h, c.hsl.s, c.hsl.l);
	return (c);
}
