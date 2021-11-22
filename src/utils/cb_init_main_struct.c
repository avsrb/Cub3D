#include "../../inc/cub3d.h"

static void	cb_init_mlx(t_win *win)
{
	win->win_width = WIN_WIDTH;
	win->win_height = WIN_HEIGHT;
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIN_WIDTH, \
								WIN_HEIGHT, "cub3D");
	if (win->win_ptr == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	win->img_ptr = mlx_new_image(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	win->addr = mlx_get_data_addr(win->img_ptr, &win->bpp, &win->line_length,
			&win->endian);
}

static void	init_lodev_stuct(t_lodev *lodev)
{
	lodev->step_x = 0;
	lodev->step_y = 0;
	lodev->camera_x = 0;
	lodev->ray_dir_x = 0;
	lodev->ray_dir_y = 0;
	lodev->map_x = 0;
	lodev->map_y = 0;
	lodev->side_dist_x = 0;
	lodev->side_dist_y = 0;
	lodev->delta_dist_x = 0;
	lodev->delta_dist_y = 0;
	lodev->perp_wall_dist = 0;
	lodev->flag_hit = 0;
	lodev->side = '0';
}

void	cb_init_main_struct(t_main *data)
{
	data->zoom = 8;
	cb_init_mlx(data->win);
	data->txrs = cb_malloc_x(sizeof(t_txrs));
	init_lodev_stuct(data->lodev);
	open_texture(data);
}
