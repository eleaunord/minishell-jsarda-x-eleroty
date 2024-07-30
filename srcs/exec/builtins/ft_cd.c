/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 20:21:58 by juliensarda       #+#    #+#             */
/*   Updated: 2024/07/30 18:08:52 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_errors(void)
{
	ft_errors_exec(1, strerror(errno), "malloc", errno);
}

void	update_pwd(t_minishell *shell, t_node *data, char cwd[])
{
	char	**new_tab;
	char	*temp;
	char	*temp_str;

	new_tab = malloc(sizeof(char *) * 4);
	if (!new_tab)
		return (cd_errors());
	new_tab[0] = ft_strdup("export");
	if (!new_tab[0])
		return (cd_errors(), free_tab(new_tab));
	temp = ft_strdup(get_key_value(shell->env, "PWD"));
	if (!temp)
		temp = ft_strdup(getcwd(cwd, PATH_MAX));
	temp_str = ft_strjoin("OLDPWD=", temp);
	free(temp);
	if (!temp_str)
		return (cd_errors(), free_tab(new_tab));
	new_tab[1] = temp_str;
	temp_str = ft_strjoin("PWD=", getcwd(cwd, PATH_MAX));
	if (!temp_str)
		return (cd_errors(), free_tab(new_tab));
	new_tab[2] = temp_str;
	new_tab[3] = NULL;
	ft_export(data, shell, new_tab);
	free_tab(new_tab);
}

void	ft_cd(t_node *data, t_minishell *shell, char **args)
{
	int		cd_ret;
	char	cwd[PATH_MAX];

	(void)cd_ret;
	(void)args;
	if (count_args(data->args) >= 3)
		return (ft_errors_exec(1, " too many arguments", "cd", 1));
	if (!data->args[1])
	{
		if (check_key(shell->env, "HOME"))
			return (ft_errors_exec(1, " HOME not set", "cd", 1));
		cd_ret = chdir(get_path_value(shell, "HOME"));
		if (cd_ret != 0)
			return (ft_errors_exec(1, strerror(errno), "cd", 1));
		update_pwd(shell, data, cwd);
		return ;
	}
	cd_ret = chdir(data->args[1]);
	if (cd_ret != 0)
		return (ft_errors_exec(1, strerror(errno), "cd", 1));
	update_pwd(shell, data, cwd);
	g_status = 0;
}
