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

void set_player_direction(t_plr *plr, char c)
{
	if (c == 'N')
	{
		plr->dir_x = 0.012389;
		plr->dir_y = -0.999923;
		plr->plane_x = -0.659949;
		plr->plane_y = -0.008177;
		plr->angle = ft_degree_to_ratio(270);
	}
	else if (c == 'S')
	{
		plr->dir_x = 0.029200;
		plr->dir_y = 0.999574;
		
		plr->plane_x = 0.659719;
		plr->plane_y = -0.019272;
		plr->angle = ft_degree_to_ratio(90);
	}
	else if (c == 'W')
	{
		plr->dir_x = -1.0;
		plr->dir_y = 0;
		plr->plane_x = 0;
		plr->plane_y = 0.66;
		plr->angle = ft_degree_to_ratio(180);
	}
	else if (c == 'E')
	{
		plr->dir_x = 0.998295;
		plr->dir_y = -0.058374;
		plr->plane_x = -0.038527;
		plr->plane_y = -0.658875;
		plr->angle = ft_degree_to_ratio(0);
	}
}

void	setup_texture(t_main *all, t_txr *txr, char *file)
{
	int	sz[2];

	txr->img = mlx_xpm_file_to_image(all->win->mlx_ptr, file, &sz[0], &sz[1]);
	if (!txr->img)
		ft_error("Not read xmp file\n");
	if (sz[0] != 64 || sz[1] != 64)
		ft_error("invalid xpm size\n");
	txr->addr = mlx_get_data_addr(txr->img, &txr->bpp, &txr->size_line, &txr->endian);
	txr->bpp = txr->bpp / 8;
}

void	open_texture(t_main *all)
{
	all->txrs->north = cb_malloc_x(sizeof(t_txr));
	setup_texture(all, all->txrs->north, all->map->xpm[0]);
	all->txrs->south = cb_malloc_x(sizeof(t_txr));
	setup_texture(all, all->txrs->south, all->map->xpm[1]);
	all->txrs->west = cb_malloc_x(sizeof(t_txr));
	setup_texture(all, all->txrs->west, all->map->xpm[2]);
	all->txrs->east = cb_malloc_x(sizeof(t_txr));
	setup_texture(all, all->txrs->east, all->map->xpm[3]);
}

void	clean_map(t_map *m)
{
	int		y;
	int 	i;
	char **map_clean;

	m->width -= 2;
	m->height -= 2;
	y = -1;
	i = 0;
	map_clean = cb_malloc_x(sizeof(char *) * m->height + 1);
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

void	find_player(t_plr *plr, t_map *m)
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
				plr->y = (float)y + 0.1F; //todo Stan addiction
				plr->x = (float)x + 0.1F; //todo Stan addiction
				set_player_direction(plr, m->map[y][x]);
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
	find_player(all->plr, all->map);
	open_texture(all);
	return (0);
}
