#include "../../../includes/minishell.h"

void	print_env(t_env *list)
{
	t_env	*start;

	start = list;
	if (!list)
		return ;
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
int	init_env_null(t_minishell *data, int mode)
{
	t_env	*list;
	char	*tmp;
	char	cwd[PATH_MAX];

	list = NULL;
	tmp = ft_strdup("SHLVL=1");
	if (!tmp)
		return (0);
	if (!append(&list, tmp))
	{
		free(tmp);
		free_env_list(list);
		return (0);
	}
	free(tmp);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	tmp = ft_strjoin("PWD=", ft_strdup(cwd));
	if (!tmp)
		return (0);
	if (!append(&list, tmp))
	{
		free(tmp);
		free_env_list(list);
		return (0);
	}
	if (mode == 0)
	{
		free(tmp);
		tmp = ft_strdup("_=/usr/bin/env");
		if (!tmp)
			return (0);
		if (!append(&list, tmp))
		{
			free(tmp);
			free_env_list(list);
			return (0);
		}
	}
	if (mode == 0)
		data->env = list;
	else
		data->env_dup = list;
	return (1);
}

char	*recup_shlvl(char *tmp)
{
	char	**split;
	int		lvl;
	char	*char_lvl;

	split = ft_split(tmp, '=');
	if (!split)
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	lvl = atoi(split[1]);
	free(tmp);
	char_lvl = ft_itoa(lvl + 1);
	if (!char_lvl)
	{
		free_split(split);
		return (NULL);
	}
	tmp = ft_strjoin("SHLVL=", char_lvl);
	free(char_lvl);
	free_split(split);
	if (!tmp)
		return (NULL);
	return (tmp);
}

int	init_env_dup(t_minishell *data, char **env)
{
	t_env	*list;
	int		i;
	char	*tmp;

	if (env[0] == 0)
	{
		if (!init_env_null(data, 1))
			return (0);
		return (1);
	}
	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = strdup(env[i]);
		if (ft_strstr(tmp, "SHLVL"))
			tmp = recup_shlvl(tmp);
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

	if (env[0] == 0)
	{
		if (!init_env_null(data, 0))
			return (0);
		return (1);
	}
	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = strdup(env[i]);
		if (ft_strstr(tmp, "SHLVL"))
			tmp = recup_shlvl(tmp);
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
