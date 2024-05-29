//
// Initialize an environment variable list from an array of strings (env) and stores it in a structure (t_env).
// typedef struct s_env
// {
// 	char				*key;
// 	char				*value;
// 	struct s_env		*next;
// 	struct s_env		*prev;
// }						t_env;
// // Function to print the environment list
// void	print_env(t_env *list)
// {
// 	t_env	*start;

// 	start = list;
// 	if (!list)
// 	{
// 		printf("The environment list is empty.\n");
// 		return ;
// 	}
// 	do
// 	{
// 		printf("%s\n", list->value);
// 		list = list->next;
// 	} while (list != start);
// }
//
// Allocates memory for a new t_env element and initializes its value field with the provided elem.
// static int	list_new_elem_str(t_env **new, char *elem)
// {
// 	(*new) = malloc(sizeof(t_env));
// 	if (*new == NULL)
// 		return (0);
// 	(*new)->value = elem;
// 	(*new)->next = NULL;
// 	(*new)->prev = NULL;
// 	return (1);
// }
// // Add the first element to the list.
// static void	add_first(t_env **list, t_env *new)
// {
// 	(*list) = new;
// 	(*list)->prev = *list;
// 	(*list)->next = *list;
// }
// //  Appends a new element to an existing list.
// int	append(t_env **list, char *elem)
// {
// 	t_env	*new;

// 	if (!list_new_elem_str(&new, elem))
// 		return (0);
// 	if (!(*list))
// 		add_first(list, new);
// 	else
// 	{
// 		new->prev = (*list)->prev; // last element of the existing list
// 		new->next = (*list);
// 		(*list)->prev->next = new;
// 		(*list)->prev = new;
// 	}
// 	return (1);
// }
// int	init_env(t_minishell *data, char **env)
// {
// 	t_env	*list;
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	list = NULL;
// 	while (env[i])
// 	{
// 		tmp = ft_strdup(env[i]);
// 		if (!tmp)
// 		{
// 			free_env_list(list);
// 			return (0);
// 		}
// 		if (!append(&list, tmp))
// 		{
// 			free_env_list(list);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	data->env = list;
// 	return (0);
// }


// void	print_env(t_env *list)
// {
// 	t_env	*start;

// 	start = list;
// 	if (!list)
// 	{
// 		printf("The environment list is empty.\n");
// 		return ;
// 	}
// 	do
// 	{
// 		printf("Key: %s, Value: %s\n", list->key, list->value);
// 		list = list->next;
// 	} while (list != start);
// }

// char	*minishell_expansion(char *token, t_minishell *mini)
// {
// 	char	*str;
// 	char	*tmp;

// 	str = NULL;
// 	// If the token starts with a single quote (')
// 	if (token[0] == 39) // 39 is the ASCII value for single quote
// 		str = ft_strtrim(token, "\'");
// 	// If the token does not contain a dollar sign ($)
// 	if (ft_strchr(token, '$') == NULL)
// 		return (NULL);
// 		str = ft_strdup(token);
// 	// If str is not NULL at this point, return it (token is not expandable)
// 	if (str != NULL)
// 		return (str);
// 	// Expand variables in the token
// 	str = expand_variables(token, mini);
// 	// If the token starts with a double quote (")
// 	if (*token == 34)
// 	{ // 34 is the ASCII value for double quote
// 		tmp = str;
// 		// Remove double quotes from the expanded string
// 		str = ft_strtrim(str, "\"");
// 		free(tmp);
// 		return (str);
// 	}
// 	return (str);
// }