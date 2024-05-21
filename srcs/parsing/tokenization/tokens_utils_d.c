

// #include "../../includes/minishell.h"

// int	is_space(const char num)
// {
// 	if (num == 32 || (num >= 9 && num <= 13))
// 		return (1);
// 	else
// 		return (0);
// }

// void	insert_node(t_list *elem, t_list *new_elem)
// {
// 	if (elem)
// 	{
// 		if (elem->next)
// 		{
// 			new_elem->next = elem->next;
// 			elem->next->prev = new_elem;
// 		}
// 		new_elem->prev = elem;
// 		elem->next = new_elem;
// 	}
// 	else
// 		elem = new_elem;
// }