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
		if (!ft_strlen(line) && m->map_l && !m->map_done)
			m->map_done = true;
		if (ft_strlen(line))
		{
			if (m->map_done)
				ft_error("invalid map\n");
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


void	clean_map(t_map *m)
{
	int		y;
	int 	i;
	char **map_clean;

	m->width -= 2;
	m->height -= 2;
	y = -1;
	i = 0;
	map_clean = cb_malloc_x(sizeof(char *) * m->height);
	while (++y < m->height + 2)
	{
		if (y != 0 && y != (m->height + 1))
			map_clean[i++] = ft_strdup(m->map[y] + 1);
		free(m->map[y]);
	}
	map_clean[i] = NULL;
	free(m->map);
	m->map = map_clean;
}

void	find_player(t_map *m, t_plr *p)
{
	int	y;
	int	x;

	y = 0;
	while (m->map[y])
	{
		x = 0;
		while (m->map[y][x])
		{
			if (m->map[y][x] == 'N' || m->map[y][x] == 'S'
			|| m->map[y][x] == 'W' || m->map[y][x] == 'E')
			{
				p->y = y;
				p->x = x;
				return;
			}
			x++;
		}
		y++;
	}
}

int	parsing(int ac, char *file, t_main *all)
{
	int	fd;

	fd = check_file(ac, file);
	parsing_param(fd, all->map);
	close(fd);
	check_simbol(all->map->map_l);
	make_map(all->map);
	check_map(all->map);
	clean_map(all->map);
	if (check_double_player(all->map))
		ft_error("the player must be alone\n");
	if (all->map->param_done == false)
		ft_error("map not valid\n");
	find_player(all->map, all->plr);
	return (0);
}
