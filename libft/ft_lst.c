#include "../includes/minishell.h"

void	ft_putendl_fd(char const *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	write(fd, "\n", 1);
}

void	ft_lstclear(t_tokens **lst, void (*del)(void *))
{
	t_tokens *current;
	t_tokens *tmp;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		(del)(tmp->content);
		(free)(tmp);
	}
	*lst = NULL;
}

t_tokens	*ft_lstlast(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*last;

	if (NULL == lst)
		return ;
	if (NULL == *lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

t_tokens	*ft_lstnew(void *content, int type)
{
	t_tokens	*node;

	node =(t_tokens *) ft_calloc(1, sizeof(t_tokens));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->type = type;
	node->next = NULL;
	return (node);
}


