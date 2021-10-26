#include "../../inc/cub3d.h"

char	**make_map(t_list **head, int size)
{
	char	**map = ft_calloc(size + 1, sizeof(char *));
	int		i = -1;
	t_list	*tmp = *head;

	while (tmp)
	{
		map[++i] = tmp->val;
		tmp= tmp->next;
	}
	i = -1;
	while (map[++i])
		ft_putendl_fd(map[i], STDOUT);
	return (map);
}

int		parsing(int argc, char **argv)
{
	int		fd;
	char	*line = NULL;
	t_list	*head = NULL;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error(NULL);
	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	make_map(&head, ft_lstsize(head));
}

int	main(int argc, char **argv)
{
	parsing(argc, argv);
}

