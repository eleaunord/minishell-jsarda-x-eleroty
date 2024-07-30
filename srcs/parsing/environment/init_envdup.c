/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:47:31 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 11:58:02 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_env_var_dup(char *env_var)
{
	char	*processed_var;

	processed_var = ft_strdup(env_var);
	if (ft_strstr(processed_var, "SHLVL"))
	{
		processed_var = recup_shlvl(processed_var);
	}
	return (processed_var);
}

int	append_env_vars_dup(t_env **list, char **env, int i)
{
	char	*tmp;

	tmp = process_env_var_dup(env[i]);
	if (!tmp)
	{
		free_env_list(*list);
		return (0);
	}
	if (!append(list, tmp))
	{
		free(tmp);
		free_env_list(*list);
		return (0);
	}
	free(tmp);
	return (1);
}

int	init_env_dup_from_array(t_minishell *data, char **env)
{
	t_env	*list;
	int		i;

	list = NULL;
	i = 0;
	while (env[i])
	{
		if (!append_env_vars_dup(&list, env, i))
		{
			return (0);
		}
		i++;
	}
	data->env_dup = list;
	return (1);
}

int	init_env_dup(t_minishell *data, char **env)
{
	if (env[0] == 0)
	{
		return (init_env_null(data, 1));
	}
	return (init_env_dup_from_array(data, env));
}
