#include "../../../includes/minishell.h"

void	print_env(t_env *list)
{
	t_env	*start;

	start = list;
	if (!list)
	{
		printf("The environment list is empty.\n");
		return ;
	}
	printf("%s=%s\n", list->key, list->value);
	list = list->next;
	while (list != start)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
}

void	add_first(t_env **list, t_env *new)
{
	(*list) = new;
	(*list)->prev = *list;
	(*list)->next = *list;
}

int	append(t_env **list, char *elem)
{
	t_env	*new;

	if (!list_new_elem_str(&new, elem))
		return (0);
	if (!(*list))
		add_first(list, new);
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}
int init_env_dup(t_minishell *data, char **env)
{
	t_env *list;
	int i;
	char *tmp;

	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = strdup(env[i]);
		if (!tmp)
		{
			free_env_list(list);
			return (0);
		}
		if (!append(&list, tmp))
		{
			free(tmp);
			free_env_list(list);
			return (0);
		}
		free(tmp);
		i++;
	}
	data->env_dup = list;
	return (1);
}
int	init_env(t_minishell *data, char **env)
{
	t_env	*list;
	int		i;
	char	*tmp;

	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = strdup(env[i]);
		if (!tmp)
		{
			free_env_list(list);
			return (0);
		}
		if (!append(&list, tmp))
		{
			free(tmp);
			free_env_list(list);
			return (0);
		}
		free(tmp);
		i++;
	}
	data->env = list;
	return (1);
}
