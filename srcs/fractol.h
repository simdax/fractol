/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 12:48:31 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/31 17:38:06 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "math.h"
# include "stdio.h"
# include "fcntl.h"
# include "stdlib.h"
# include "unistd.h"
# include <pthread.h>
# include "libft.h"
# include <complex.h>
# include "keys.h"

# define SIZE_X 1000
# define SIZE_Y	1000

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

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	int			bpp;
	int			endian;
	int			sl;
}				t_img;

typedef struct	s_libx
{
	void		*win;
	void		*mlx;
	t_img		*img;
	char		*name;
}				t_libx;

typedef struct	s_flags
{
	double		x;
	double		y;
	int			iterations;
	int			color1;
	int			color2;
	double		factor;
}				t_flags;

typedef struct	s_fractal
{
	double		min_re;
	double		max_re;
	double		min_im;
	double		max_im;
	double		re_factor;
	double		im_factor;
	float		max_iterations;
	int			(*f)(int, double, double, t_flags*);
}				t_fractal;

typedef struct	s_thread
{
	t_fractal	*set;
	int			*data;
	int			from;
	int			to;
	int			id;
	t_flags		*flags;
}				t_thread;

typedef struct	s_prog
{
	t_libx		*libx;
	t_fractal	*set;
	t_flags		*flags;
}				t_prog;

double			ft_abs_d(double d);
int				balance_du_gros_thread(t_fractal *set, int *data,
								t_flags *flags);
int				julia(int n, double c_re, double c_im, t_flags *flags);
int				mandelbrot(int n, double c_re, double c_im, t_flags *flags);
int				mandelbrot3(int n, double c_re, double c_im, t_flags *flags);
int				mandelbrot2(int n, double c_re, double c_im, t_flags *flags);
int				burningship(int n, double c_re, double c_im, t_flags *flags);
void			*calc_set(void *v);
void			hydrate_set(t_fractal *set);
void			draw(t_prog *prog);
void			init_set(t_fractal *set);
int				clos(void *d);
int				go(t_prog *prog);
void			go_f(int (*f)(int, double, double, t_flags*), t_prog *prog);
int				keyb_hook(int keycode, t_prog *data);
int				mouse_hook(int button, int x, int y, t_prog *prog);
int				mouse_hook_l(int x, int y, t_prog *data);
int				mouse_hook_r(int x, int y, t_prog *data);
int				mouse_move(int x, int y, t_prog *prog);
t_color			create_color(float h, float s, float l);
int				color2hex(t_color c);
int				hsl2hex(float h, float s, float l);
t_color			update(t_color c, float h, float s, float l);

#endif
