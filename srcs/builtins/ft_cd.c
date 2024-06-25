/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:01:41 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/24 18:26:52 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd(t_minishell *data, t_node *node)
{
	char	**new_tab;
	char	*tmp;
	char	cwd[PATH_MAX];

	new_tab = malloc(sizeof(char *) * 4);
	if (!new_tab)
		return ;
	new_tab[0] = ft_strdup("export");
	if (!new_tab[0])
	{
		free(new_tab);
		return ;
	}
	tmp = ft_strdup(get_key_value(data->env, "PWD"));
	if (!tmp)
		return ; // ft_error + free new_tab and new_tab[0]
	new_tab[1] = ft_strdup(ft_strjoin("OLDPWD=", tmp));
	free(tmp);
	if (!new_tab[1])
	{
		free(new_tab[0]);
		free(new_tab);
		return ;
	}
	new_tab[2] = ft_strdup(ft_strjoin("PWD=", getcwd(cwd, PATH_MAX)));
	if (!new_tab[2])
	{	
		free(new_tab[0]);
		free(new_tab[1]);
		free(new_tab);
		return ;
	}
	new_tab[3] = NULL;
	ft_export(data, node, new_tab);
}

void	ft_error(char *message, char *err, int exit_status, t_minishell *data)
{
	if (err)
	{
		ft_putstr_fd(message, 2);
		ft_putendl_fd(err, 2);
	}
	else
		ft_putendl_fd(message, 2);
	data->exit_status = exit_status;
}

int	check_key(t_env *env, char *key)
{
	t_env	*start;
	t_env	*current;

	current = env;
	start = env;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (0);
		current = current->next;
		if (current == start)
			return (1);
	}
	return (1);
}

void	ft_cd(t_minishell *data, t_node *node, char **args)
{
	int	cd_ret;

	if (count_args(args) >= 3)
		return (ft_error("cd: too many arguments", NULL, 1, data));
	if (!args[1])
	{
		if (check_key(data->env, "HOME"))
			return (ft_error("cd : HOME not set", NULL, 1, data));
		cd_ret = chdir(get_path_value(data, "HOME"));
		if (cd_ret != 0)
			ft_error("cd : ", strerror(errno), 1, data);
		update_pwd(data, node);
		return ;
	}
	cd_ret = chdir(args[1]);
	update_pwd(data, node);
	if (cd_ret != 0)
		ft_error("cd : ", strerror(errno), 1, data);
}
