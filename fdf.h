/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:48:31 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/19 19:01:23 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "math.h"
# include "stdio.h"
# include "fcntl.h"
# include "stdlib.h"
# include "unistd.h"
# include "libft.h"
# include <get_next_line.h>

# define SIZE_X	1200
# define SIZE_Y	1200

typedef struct	s_rgb
{
	float		r;
	float		g;
	float		b;
}				t_rgb;

typedef struct	s_hsl
{
	float		h;
	float		s;
	float		l;
}				t_hsl;

typedef struct	s_color
{
	t_rgb	rgb;
	t_hsl	hsl;
}				t_color;

typedef struct	s_point
{
	float			x;
	float			y;
	float			z;
}				t_point;

typedef struct	s_line
{
	t_point			origin;
	float			slope;
	int				steps;
	t_point			goal;
}				t_line;

typedef struct	s_color_point
{
	t_point		point;
	t_color		color;
}				t_color_point;

typedef struct	s_map
{
	int			len;
	int			rows;
	int			cols;
	float		c1;
	float		c2;
	int			*values;
}				t_map;

typedef struct	s_matrix
{
	int			len;
	int			cols;
	int			rows;
	t_point		*points;
	t_map		*map;
}				t_matrix;

typedef struct	s_libx
{
	void			*win;
	void			*mlx;
}				t_libx;

typedef struct	s_prog
{
	t_libx		*libx;
	t_matrix	*matrix;
	t_color		color;
}				t_prog;

t_point			proj_ortho(int nb, const t_map *z_points);
int				tab_of_points(char *file, t_matrix *matrix);
t_map			*parse(char *file_name);
void			draw(t_matrix *matrix, t_color c, t_libx *libx);
void			line(t_point x1, t_point x2, t_color color, t_libx *libx);
void			event_manager(int keycode, t_matrix *matrix);
int				transform(int keycode, void *arg);
t_color			create_color(float h, float s, float l);
int				color2hex(t_color c);
int				hsl2hex(float h, float s, float l);
t_color			update(t_color c, float h, float s, float l);

#endif
