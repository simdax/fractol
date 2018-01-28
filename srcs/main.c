/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/28 20:13:49 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keyb_hook(int keycode, void *data)
{
	event_manager(keycode, ((t_prog*)data)->matrix);
	return (0);
}
	
int		mouse_hook(int button, int x, int y, void *data)
{
	t_prog		*prog;

	prog = data;
	prog->set->min_im += 0.2300001;
	prog->set->min_re += 0.2300001;
	prog->set->max_re += -0.2300001;
	prog->set->max_im += -0.2300001;
	prog->set->re_factor = (prog->set->max_re - prog->set->min_re) / (SIZE_X - 1);
	prog->set->im_factor = (prog->set->max_im - prog->set->min_im) / (SIZE_Y - 1);
	calc_set(prog->set, prog->libx->img->data);
	mlx_put_image_to_window(prog->libx->mlx, prog->libx->win,
						prog->libx->img->ptr, 0, 0);
	return(0);
}

void		take_flags(int argc, char **argv, t_fractal *set)
{
	/* set->min_re = argc > 1? parse(argv[1]) : -1.0; */
	/* set->max_re = argc > 1? parse(argv[1]) : -1.0; */
	/* set->min_im = argc > 1? parse(argv[1]) : -1.0; */
	/* set->min_re = argc > 1? parse(argv[1]) : -1.0; */
	set->max_re = 2.0;
	set->min_re = -2.0;
	set->max_im = 2.0;
	set->min_im = -2.0;
	set->max_iterations = 50;
	set->re_factor = (set->max_re - set->min_re) / (SIZE_X - 1);
	set->im_factor = (set->max_im - set->min_im) / (SIZE_Y - 1);
	return ;
}

int			main(int argc, char **argv)
{
	t_libx		libx;
	t_prog		prog;
	t_fractal	set;
	
	take_flags(argc, argv, &set);
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, SIZE_X, SIZE_Y, "fractol");
	libx.img = &(t_img){mlx_new_image(libx.mlx, SIZE_X, SIZE_Y)};
	libx.img->data = (int*)mlx_get_data_addr(
		libx.img->ptr, &(libx.img->bpp), &(libx.img->sl), &(libx.img->endian));
	prog = (t_prog){&libx, 0, &set};
	calc_set(&set, libx.img->data);
	mlx_put_image_to_window(libx.mlx, libx.win, libx.img->ptr, 0, 0);
	mlx_hook(libx.win, 4, 4, mouse_hook, &prog);
	mlx_hook(libx.win, 2, 3, keyb_hook, &prog);
	mlx_loop(libx.mlx);
	return (0);
}
