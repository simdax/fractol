/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:48:31 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/03 13:06:06 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "math.h"
# include "stdio.h"
# include "fcntl.h"
# include "stdlib.h"
# include "libft.h"

# define SIZE_X				1600
# define SIZE_Y				1600
# define OFFSET_X			500
# define OFFSET_Y			500
# define SPACE				10

typedef struct	s_rgb {
	float 		r;
	float 		g;
	float 		b;
}				t_rgb;

typedef struct	s_hsl {
	float		h;
	float		s;
	float		l;
}				t_hsl;

typedef struct	s_color
{
	t_rgb	rgb;
	t_hsl	hsl;
}				t_color;

typedef struct		s_libx
{
	void			*win;
	void			*mlx;
}					t_libx;

typedef struct		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef struct		s_line
{
	t_point			origin;
	float			slope;
	int				steps;
}					t_line;

typedef struct		s_matrix
{
	int			len;
	int			cols;
	int			rows;
	t_point		*points;
}					t_matrix;

typedef struct		s_prog
{
	t_libx		*libx;
	t_matrix	*matrix;
}					t_prog;

typedef struct		s_map
{
	int			len;
	int			rows;
	int			cols;
	int			*values;
}					t_map;

t_map				*parse(char *file_name);
void				line(t_point x1, t_point x2, long color, t_libx *libx);
int					transform(int keycode, void *arg);
void				draw(t_matrix *matrix, long color, t_libx *libx);
int					tab_of_points(char *file, int space, t_matrix *matrix);
void				event_manager(int keycode, t_matrix *matrix);
t_color				create_color(float h, float s, float l);
int					color2hex(t_color c);

#endif
