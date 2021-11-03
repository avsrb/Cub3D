#include "../../inc/cub3d.h"

t_lst	*ft_lstlast(t_lst *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstdelone(t_lst *lst)
{
	if (lst->val)
		free(lst->val);
	if (lst)
		free(lst);
	lst = NULL;
}

void	ft_lstclear(t_lst **lst)
{
	t_lst	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst);
			(*lst) = tmp;
		}
	}
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

t_lst	*ft_lstnew(char *content)
{
	t_lst	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->val = content;
	list->next = NULL;
	return (list);
}
