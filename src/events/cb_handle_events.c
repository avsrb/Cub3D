#include "../../inc/cub3d.h"

int	terminate(t_win *win)
{
	mlx_destroy_window(win->mlx, win->win);
	win->win = NULL;
	ft_putendl_fd("Adios, amigo!", STDOUT_FILENO);
	exit (0);
}

int	cb_handle_events(t_win *win)
{
	mlx_hook(win->win, 17, 0, &terminate, win);
	return (0);
}