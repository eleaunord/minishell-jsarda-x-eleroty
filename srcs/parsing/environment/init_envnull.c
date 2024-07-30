/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envnull.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:52:21 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 11:53:38 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_underscore_var(t_env **list)
{
	char	*tmp;

	tmp = ft_strdup("_=/usr/bin/env");
	if (!tmp)
		return (0);
	if (!append(list, tmp))
	{
		free(tmp);
		free_env_list(*list);
		return (0);
	}
	free(tmp);
	return (1);
}

int	init_pwd_var(t_env **list)
{
	char	cwd[PATH_MAX];
	char	*tmp;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	tmp = ft_strjoin("PWD=", ft_strdup(cwd));
	if (!tmp)
		return (0);
	if (!append(list, tmp))
	{
		free(tmp);
		free_env_list(*list);
		return (0);
	}
	free(tmp);
	return (1);
}

int	init_shlvl_var(t_env **list)
{
	char	*tmp;

	tmp = ft_strdup("SHLVL=1");
	if (!tmp)
		return (0);
	if (!append(list, tmp))
	{
		free(tmp);
		free_env_list(*list);
		return (0);
	}
	free(tmp);
	return (1);
}

int	init_env_null(t_minishell *data, int mode)
{
	t_env	*list;

	list = NULL;
	if (!init_shlvl_var(&list))
		return (0);
	if (!init_pwd_var(&list))
		return (0);
	if (mode == 0)
	{
		if (!init_underscore_var(&list))
			return (0);
		data->env = list;
	}
	else
	{
		data->env_dup = list;
	}
	return (1);
}
