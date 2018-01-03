/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:37:00 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/03 13:49:04 by scornaz          ###   ########.fr       */
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
	x = c * (1 - fabs(fmod(hue / 60,  2) - 1));
	m = light - c / 2;
	rgb = (0 <= hue && hue <= 60) ?	(t_rgb){c, x, 0} :
	(60 <= hue && hue <= 120) ?		(t_rgb){x, c, 0} :
	(120 <= hue && hue <= 180) ?	(t_rgb){0, c, x} :
	(180 <= hue && hue <= 240) ?	(t_rgb){0, x, c} :
	(240 <= hue && hue <= 300) ?	(t_rgb){x, 0, c} :
	(300 <= hue && hue <= 360) ?	(t_rgb){c, 0, x} :
	(t_rgb){};
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

int		color2hex(t_color c)
{
	long res;

	res = (int)c.rgb.r << 16;
	res += (int)c.rgb.g << 8;
	res += (int)c.rgb.b;
	return (res);
}

/* int main() */
/* { */
/* 	t_color c; */

/* 	c = create_color(37, 0.15, 0.5); */
/* 	printf("%#x\n", color2hex(c)); */
/* 	c = create_color(37, 0.15, 0.15); */
/* 	printf("%#x\n", color2hex(c)); */
/* 	c = create_color(37, 0.915, 0.5); */
/* 	printf("%#x\n", color2hex(c)); */
/* 	c = create_color(37, 0.515, 0.5); */
/* 	printf("%#x\n", color2hex(c)); */
/* 	c = create_color(237, 0.15, 0.5); */
/* 	printf("%#x\n", color2hex(c)); */
/* 	c = create_color(137, 0.15, 0.5); */
/* 	printf("%#x\n", color2hex(c)); */
/* } */
