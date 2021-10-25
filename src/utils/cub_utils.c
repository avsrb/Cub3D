#include "../../inc/cub3d.h"

void	cb_init(t_win	*win)
{
	win->mlx = mlx_init();
	if (win->mlx == NULL)
	{
		free(win->mlx);
		printf("cub3d error: %s\n", strerror(errno));//todo
		return ;
	}
	win->win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (win->win == NULL)
	{
		free(win->win);
		printf("cub3d error: %s\n", strerror(errno));//todo
		return ;
	}
}



