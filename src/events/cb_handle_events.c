#include "../../inc/cub3d.h"

int	cb_terminate(t_win *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	win->win_ptr = NULL;
	ft_putendl_fd("Adios, amigo!", STDOUT_FILENO);
	exit (0);
}

int	cb_handle_events(t_win *win)
{
	mlx_hook(win->win_ptr, 17, 0, &cb_terminate, win);
	return (0);
}