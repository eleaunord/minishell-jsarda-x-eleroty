#include "../../../includes/minishell.h"

/*
If no environment exists we create a minimal env OR return 0 ?

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

// Initialize an environment variable list from an array of strings (env) and stores it in a structure (t_env).

// Prints the environment list
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
// Allocates memory for a new t_env element and initializes its fields with the provided elem.
static int	list_new_elem_str(t_env **new, char *elem)
{
	char	*equal_sign;

	(*new) = malloc(sizeof(t_env));
	if (*new == NULL)
		return (0);
	(*new)->str = strdup(elem); // allocate and copy the entire string
	if ((*new)->str == NULL)
	{
		free(*new);
		return (0);
	}
	equal_sign = strchr(elem, '=');
	if (equal_sign)
	{
		(*new)->key = strndup(elem, equal_sign - elem); // allocate and copy key
		if ((*new)->key == NULL)
		{
			free((*new)->str);
			free(*new);
			return (0);
		}
		(*new)->value = strdup(equal_sign + 1); // allocate and copy value
		if ((*new)->value == NULL)
		{
			free((*new)->str);
			free((*new)->key);
			free(*new);
			return (0);
		}
	}
	else
	{
		(*new)->key = strdup(elem); // allocate and copy the whole string as key
		if ((*new)->key == NULL)
		{
			free((*new)->str);
			free(*new);
			return (0);
		}
		(*new)->value = NULL; // no value
	}
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

// Add the first element to the list.
static void	add_first(t_env **list, t_env *new)
{
	(*list) = new;
	(*list)->prev = *list;
	(*list)->next = *list;
}
//  Appends a new element to an existing list.
int	append(t_env **list, char *elem)
{
	t_env	*new;

	if (!list_new_elem_str(&new, elem))
		return (0);
	if (!(*list))
		add_first(list, new);
	else
	{
		new->prev = (*list)->prev; // last element of the existing list
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
		tmp = strdup(env[i]); // Assuming ft_strdup is similar to strdup
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
