#include "../../inc/cub3d.h"
#define DEBUG
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
	int		i;
	int 	j;
	t_lst	*lst;

	lst = *map_l;
	i = 0;
	map->map = calloc(map->height + 2, sizeof(char *));
	map->map[i] = calloc(map->width + 2, sizeof(char));
	ft_memset(map->map[0], '.', map->width + 2);
	i = 1;
	while (lst)
	{
		map->map[i] = calloc(map->width + 2, sizeof(char));
		ft_memset(map->map[i], '.', map->width + 2);
		j = 0;
		while (lst->val[j] != '\0' && j < map->width + 2)
		{
			if (lst->val[j] == ' ')
				map->map[i][j+1] = '.';
			else
				map->map[i][j+1] = lst->val[j];
			j++;
		}
		lst = lst->next;
		i++;
	}
//	map->map[i] = calloc(map->width + 2, sizeof (char));
//	ft_memset(map->map[i], '.', map->width + 2);
	map->map[i] = NULL;
	ft_lstclear(map_l);
}

int		check_wall(char **map, int x, int y)
{
	(void)map;
	(void)x;
	(void)y;
//	while (map[y][x])
//	{
//		x = 0;
//		while(map[y][x] == ' ')
//		{
//			x++;
//		}
//		if (map[y][x] != '1')
//				return (1);
//		y++;
//	}
	return (0);
}


//void	check_map(char **map)
//{

//	int	y;
//	int	x;
//
//	y = 0;
//	x = 0;
//	while (map[y][x])
//	{
//		while(map[y][x])
//		{
//			x = 0;
//			if (map[y][x] == ' ')
//				if (check_wall(map, x, y))
//					ft_error(NULL);
//			x++;
//		}
//		y++;
//	}
//}

void	make_map(t_map *data)
{
	data->height = get_height(data->map_l);
	data->width = get_width(data->map_l);
	fill_matrix(data, &data->map_l);

	#ifdef DEBUG
	{
		printf("DEBUG\n");
		printf("################# MAP START #################\n");
		for (int i = 0; data->map[i]; i++)
		{
			printf("#");
			printf("%s", data->map[i]);
			printf("#\n");
		}
		printf("################# MAP FINISH ################\n");
	}
	#endif

//	check_map(data->map);
	//	data->width = get_width(data->map);
}
