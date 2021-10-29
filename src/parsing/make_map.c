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

int	get_width(char **map)
{
	int	i;
	int	width;
	int	prev_width;

	i = 0;
	width = 0;
	prev_width = ft_strlen(map[i]);
	while (map[i])
	{
		width = ft_strlen(map[i]);
		if (width != prev_width)
			ft_error("different width in map\n");
		prev_width = width;
		i++;
	}
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
	int		i;
	t_lst	*lst;

	lst = *map_l;
	i = 0;
	while (lst)
	{
		if (lst->val[0] != '1' || lst->val[ft_strlen(lst->val) - 1] != '1')
			ft_error("not wall in map NO or SO\n");
		map->map[i] = ft_strdup(spacecutter(lst->val));
		if (i == 0)
			if (is_one(map->map[i]))
				ft_error("not wall in map WE or EA\n");
		lst = lst->next;
		i++;
	}
	if (is_one(map->map[i - 1]))
		ft_error("not wall in map WE or EA\n");
	ft_lstclear(map_l);
}

void	make_map(t_map *data)
{
	data->height = get_height(data->map_l);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	fill_matrix(data, &data->map_l);
	//	data->width = get_width(data->map);
	data->map[data->height] = NULL;
}
