#include "../../inc/cub3d.h"

void	parsing_param(int fd, t_map *m)
{
	char	*line;
	int		res;

	line = NULL;
	while (true)
	{
		res = gnl(fd, &line);
		if (res < 0)
			ft_error(NULL);
		if (!ft_strlen(line) && m->height && !m->map_done)
			m->map_done = true;
		if (ft_strlen(line))
		{
			if (m->map_done)
				ft_error("line empty in the map\n");
			if (m->param_done == true)
				ft_lstadd_back(&m->map_l, ft_lstnew(ft_strdup(line)));
			else
				get_tex_and_color(line, m);
		}
		free(line);
		if (!res)
			break ;
	}
}

//void	check_open_texture(t_main *all)
//{
//	if (!mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[0], 600, 600))
//		ft_error("can`t open texture\n");
//	if (!mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[1], 600, 600))
//		ft_error("can`t open texture\n");
//	if (!mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[2], 600, 600))
//		ft_error("can`t open texture\n");
//	if (!mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[3], 600, 600))
//		ft_error("can`t open texture\n");
//
//}

int	parsing(int ac, char *file, t_main *all)
{
	int	fd;

	fd = check_file(ac, file);
	init(all->map);
	parsing_param(fd, all->map);
	close(fd);
	check_simbol(all->map->map_l);
	make_map(all->map);
	check_map(all->map);
	if (check_double_player(all->map))
		ft_error("the player must be alone\n");
	if (all->map->param_done == false)
		ft_error("map not valid\n");
	return (0);
}
