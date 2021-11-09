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
		plr->dir = 1.5 * M_PI;
	else if (c == 'E')
		plr->dir = 0;
	else if (c == 'S')
		plr->dir = M_PI_2;
	else if (c == 'W')
		plr->dir = M_PI;
	plr->start = plr->dir - M_PI_4;
	plr->end = plr->dir + M_PI_4;
}

void	open_texture(t_main *all)
{
//	t_texture	*texture[] = {
//			&all->textures->north, &all->textures->south,
//			&all->textures->west, &all->textures->east};

	t_texture	**texture = malloc(sizeof(*texture) * 4 + 1);
	texture[0] = malloc(sizeof(texture));
	texture[1] = malloc(sizeof(texture));
	texture[2] = malloc(sizeof(texture));
	texture[3] = malloc(sizeof(texture));

//	all->textures = *texture;


	texture[0]->width = 64;
	texture[0]->height = 64;
	texture[1]->width = 64;
	texture[1]->height = 64;
	texture[2]->width = 64;
	texture[2]->height = 64;
	texture[3]->width = 64;
	texture[3]->height = 64;
	texture[0]->img = NULL;

	texture[0]->img = mlx_xpm_file_to_image(all->win->win_ptr, "./textures/NO.xpm", &texture[0]->width, &texture[0]->height);
	texture[0]->addr = mlx_get_data_addr(texture[0]->img, &texture[0]->bpp, &texture[0]->ll, &texture[0]->end);
	texture[1]->img = mlx_xpm_file_to_image(all->win->win_ptr, "./textures/NO.xpm", &texture[1]->width, &texture[1]->height);
	texture[1]->addr = mlx_get_data_addr(texture[1]->img, &texture[1]->bpp, &texture[1]->ll, &texture[1]->end);
	texture[2]->img = mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[2], &texture[2]->width, &texture[2]->height);
	texture[2]->addr = mlx_get_data_addr(texture[2]->img, &texture[2]->bpp, &texture[2]->ll, &texture[2]->end);
	texture[3]->img = mlx_xpm_file_to_image(all->win->win_ptr, all->map->xpm[3], &texture[3]->width, &texture[3]->height);
	texture[3]->addr = mlx_get_data_addr(texture[3]->img, &texture[3]->bpp, &texture[3]->ll, &texture[0]->end);
//		ft_error("can`t open texture\n");

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

void	find_player(t_plr *plr, t_map *m, t_plr *p)
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
	find_player(all->plr, all->map, all->plr);
	open_texture(all);
	return (0);
}
