#include "../../../includes/minishell.h"

void	free_t_env(t_env *env)
{
	if (env == NULL)
		return ;
	free(env->str);
	free(env->key);
	free(env->value);
	free(env);
}
t_env	*allocate_new_env(void)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (new_env == NULL)
		return (NULL);
	new_env->str = NULL;
	new_env->key = NULL;
	new_env->value = NULL;
	new_env->next = NULL;
	new_env->prev = NULL;
	return (new_env);
}

int	list_new_elem_str(t_env **new, char *elem)
{
	(*new) = allocate_new_env();
	if (*new == NULL)
		return (0);
	(*new)->str = duplicate_string(elem);
	if ((*new)->str == NULL)
	{
		free_t_env(*new);
		return (0);
	}
	if (!parse_key_value(new, elem))
	{
		free_t_env(*new);
		return (0);
	}
	return (1);
}
