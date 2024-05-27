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

// Function to print the environment list
void	print_env(t_env *list)
{
	t_env	*start;

	start = list;
	if (!list)
	{
		printf("The environment list is empty.\n");
		return ;
	}
	do
	{
		printf("%s\n", list->value);
		list = list->next;
	} while (list != start);
}
// Allocates memory for a new t_env element and initializes its value field with the provided elem.
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
