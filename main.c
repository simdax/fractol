#include "mlx.h" 

#define PUT(x, y)		mlx_pixel_put(libx->mlx, libx->win, x, y, 0x00FFFFFF);
typedef struct	s_libx
{
	void		*win;
	void		*mlx;
}				t_libx;

void	square(int x, int y, int width, t_libx *libx)
{
	int tmp;
	int tmp2;

	tmp = 0;
	while (tmp < width)
	{
		tmp2 = 0;
		while (tmp2 < width)
		{
			PUT(y + tmp2, x + tmp);
			++tmp2;
		}
		++tmp;
	}			
}

int		main()
{
	t_libx	libx;
	
	libx.mlx = mlx_init();
	libx.win = mlx_new_window(libx.mlx, 400, 400, "fdf");	
	square(20, 30, 200, &libx);
	mlx_loop(libx.mlx);
}
