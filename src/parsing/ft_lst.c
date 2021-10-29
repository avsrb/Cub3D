#include "../../inc/cub3d.h"

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

void	ft_lstadd_back(t_lst **head, t_lst *new)
{
	t_lst	*last;

	if (head && (*head) && new)
	{
		last = *head;
		if (*head == NULL)
			*head = new;
		else
		{
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
	else if (*head == NULL)
		*head = new;
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
