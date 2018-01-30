/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:05:26 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/30 17:25:31 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw(t_prog *prog)
{
	if ((balance_du_gros_thread(prog->set, prog->libx->img->data,
								prog->flags)))
		mlx_put_image_to_window(prog->libx->mlx, prog->libx->win,
								prog->libx->img->ptr, 0, 0);
	else
		exit(0);
}

int			go(t_prog *prog);

void		take_flags(char *argv, t_libx *libxs, t_prog *progs, t_fractal *sets)
{
	libxs->name = ft_strjoin("fractol : ", argv);
	progs->libx = libxs;
	progs->set = sets;
	if (!ft_strcmp(argv, "julia"))
		progs->set->f = julia;
	if (!ft_strcmp(argv, "mandelbrot"))
		progs->set->f = mandelbrot;
	go(progs);
}

void		init_set(t_fractal *set)
{
	set->max_re = 1.0;
	set->min_re = -1.0;
	set->max_im = 1.0;
	set->min_im = -1.0;
	set->max_iterations = 30;
	set->re_factor = (set->max_re - set->min_re) / (SIZE_X - 1);
	set->im_factor = (set->max_im - set->min_im) / (SIZE_Y - 1);
	return ;
}

int			go(t_prog *prog)
{
	prog->libx->win = mlx_new_window(prog->libx->mlx, SIZE_X, SIZE_Y, prog->libx->name);
	prog->libx->img = malloc(sizeof(t_img));
	prog->libx->img->ptr = mlx_new_image(prog->libx->mlx, SIZE_X, SIZE_Y);
	prog->libx->img->data = (int*)mlx_get_data_addr(
		prog->libx->img->ptr, &(prog->libx->img->bpp), &(prog->libx->img->sl), &(prog->libx->img->endian));
	init_set(prog->set);
	prog->flags = malloc(sizeof(t_flags));
	*(prog->flags) = (t_flags){0, 0, 20, 40};
	draw(prog);
	mlx_hook(prog->libx->win, 4, 4, mouse_hook, prog);
	mlx_hook(prog->libx->win, 6, 0, mouse_move, prog);
	mlx_hook(prog->libx->win, 2, 3, keyb_hook, prog);
	mlx_hook(prog->libx->win, 17, 0, clos, prog);
	return (0);
}

int			main(int argc, char **argv)
{
	int			i;
	void		*mlx;
	t_libx		*libxs;
	t_prog		*progs;
	t_fractal	*sets;

	if (argc == 1)
		argc = 2;
	else
		++argv;
	libxs = malloc(sizeof(t_libx) * (argc - 1));
	progs = malloc(sizeof(t_prog) * (argc - 1));
	sets = malloc(sizeof(t_fractal) * (argc - 1));
	i = 0;
	mlx = mlx_init();
	while (*argv)
	{
		libxs->mlx = mlx;
		take_flags(*argv, libxs, progs, sets);
		++libxs;
		++progs;
		++sets;
		++argv;
	}
	mlx_loop(mlx);
}
