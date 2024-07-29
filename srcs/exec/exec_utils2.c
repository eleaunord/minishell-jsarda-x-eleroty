/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:14:00 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 09:41:07 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_key(t_env *env, char *key)
{
	int	index;

	index = 0;
	while (env)
	{
		if (env->name && ft_strncmp(env->name, key, ft_strlen(env->name)) == 0)
			return (index);
		env = env->next;
		index++;
	}
	return (-1);
}

char	*get_path_value(t_shell *datas, char *key)
{
	int		index;
	t_env	*env;
	int		i;

	i = 0;
	env = datas->envp;
	index = get_key(env, key);
	if (index == -1)
		return (NULL);
	while (i < index)
	{
		env = env->next;
		i++;
	}
	return (env->value);
}

char	**create_char_env(t_env *env, int env_size)
{
	t_env	*temp_env;
	char	**dest;
	int		i;

	i = -1;
	if (!env)
		return (NULL);
	dest = malloc(sizeof(char *) * (env_size + 1));
	if (!dest)
		return (NULL);
	temp_env = env;
	while (++i < env_size)
	{
		dest[i] = ft_strdup(temp_env->line);
		if (!dest[i])
		{
			while (i > 0)
				free(dest[--i]);
			return (free(dest), NULL);
		}
		temp_env = temp_env->next;
	}
	dest[i] = NULL;
	return (dest);
}

int	get_env_list_size(t_env *list)
{
	int	count;

	count = 0;
	if (!list)
		return (0);
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

void	handle_heredoc(t_shell *shell, t_node *data)
{
	int	i;

	ft_recup(shell);
	while (data)
	{
		if (data->is_hd)
		{
			i = 0;
			while (data->limiter_hd[i])
			{
				get_tmp_file(data);
				heredoc(data, shell, data->limiter_hd[i++], data->tmpfile_hd);
				if (g_return_satus == 130)
					break ;
			}
			if (g_return_satus == 130)
				break ;
		}
		data = data->next;
	}
}
