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

char	*spacecutter(char *str)
{
	char	*pstr;
	int		i;

	pstr = str;
	i = 0;
	if (*str == '\0')
		return (NULL);
	while (*str != '\0')
	{
		if (*str != ' ')
		{
			pstr[i] = *str;
			i++;
		}
		str++;
	}
	pstr[i] = '\0';
	return (pstr);
}

int	is_one(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '1')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

void	fill_matrix(t_map *map, t_lst **map_l)
{
	int		y;
	int 	x;
	t_lst	*lst;

	lst = *map_l;
	map->width += 2;
	map->height += 2;
	map->map = cb_malloc_x(sizeof(char *) * map->height);
//	map->map[0] = ft_calloc(map->width + 2, sizeof(char));
//	ft_memset(map->map[0], ' ', map->width + 2);
	y = 0;
	while (y < map->height)
	{
		map->map[y] = calloc(map->width, sizeof(char));
		if (y != 0 && y != (map->height - 1))
		{
			ft_strlcpy(map->map[y] + 1, lst->val, map->width);
			lst = lst->next;
		}
//		ft_memset(map->map[y], '.', map->width + 2);
//		x = 0;
//		while (lst->val[x] != '\0'&&x < map->width + 2)
//		{
//			if (lst->val[x] == ' ')
//				map->map[y][x + 1] = ' ';
//			else
//				map->map[y][x + 1] = lst->val[x];
//			x++;
//		}
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
