#include "../../../includes/minishell.h"

/*

Environment Variables
=> key-value pairs maintained by the OS and used by processes to configure their behavior.
e.g : PATH, HOME, USER, and PWD.

OLDPWD
	Purpose: OLDPWD holds the path of the previous current working directory.
			This allows users and programs to reference the last directory they were in before changing to the current directory.
	Usage: It's particularly useful in shell environments.
			For example, in the Bash shell, you can use the command cd
				- to change back to the previous directory,
				and it uses OLDPWD to know where to go.

=> duplicate the string "OLDPWD" and then add it to the environment list soo that if env initially
empty at least "OLDPWD" available

*/

// If no environment exists we create a minimal env OR return 0 ?

static int	list_new_elem_str(t_env **new, char *elem)
{
	(*new) = malloc(sizeof(t_env));
	if (*new == NULL)
		return (0);
	(*new)->value = elem;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

static void	add_first(t_env **list, t_env *new)
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
int	init_env(t_minishell *data, char **env)
{
	t_env	*list;
	int		i;
	char	*tmp;

	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
		{
			free_env_list(list);
			return (0);
		}
		if (!append(&list, tmp))
		{
			free_env_list(list);
			return (0);
		}
		i++;
	}
	data->env = list;
	return (0);
}
