#include "../../inc/cub3d.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*l_elem;

	if (lst)
	{
		if (*lst == 0)
			*lst = new;
		else
		{
			l_elem = ft_lstlast(*(lst));
			l_elem->next = new;
		}
	}
}

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstnew(char *val)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
		return (0);
	elem->val = val;
	val++;
	elem->next = NULL;
	return (elem);
}


t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
		return (lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

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

void	ft_lstdelone(t_list *lst)
{
	if (lst)
		free(lst);
	lst = NULL;
}

//int	ft_lstfindindex(t_list *lst, int f)
//{
//	t_list	*tmp;
//	int		index;
//
//	index = 1;
//	tmp = lst;
//	while (tmp && tmp->val != f)
//	{
//		tmp = tmp->next;
//		index++;
//	}
//	return (index);
//}

