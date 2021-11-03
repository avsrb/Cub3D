#include "../../inc/cub3d.h"

int	get_height(t_lst *map_l)
{
	int		height;

	height = 0;
	while (map_l)
	{
		height++;
		map_l = map_l->next;
	}
	return (height);
}

int	get_width(t_lst *map_l)
{
	int	width;
	int	max;

	max = 0;
	while (map_l)
	{
		width = ft_strlen(map_l->val);
		if (width > max)
			max = width;
		map_l = map_l->next;
	}
	width = max;
	return (width);
}

void	fill_matrix(t_map *map, t_lst **map_l)
{
	int		y;
	t_lst	*lst;

	lst = *map_l;
	map->width += 2;
	map->height += 2;
	map->map = cb_malloc_x(sizeof(char *) * map->height);
	y = 0;
	while (y < map->height)
	{
		map->map[y] = calloc(map->width, sizeof(char));
		if (y != 0 && y != (map->height - 1))
		{
			ft_strlcpy(map->map[y] + 1, lst->val, map->width);
			lst = lst->next;
		}
		y++;
	}
	map->map[y++] = NULL;
	ft_lstclear(map_l);
}

void	make_map(t_map *data)
{
	data->height = get_height(data->map_l);
	data->width = get_width(data->map_l);
	fill_matrix(data, &data->map_l);
}
