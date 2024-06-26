/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:01:41 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/26 14:10:42 by jsarda           ###   ########.fr       */
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
		return (ft_error("malloc : ", strerror(errno), 1, data));
	new_tab[0] = ft_strdup("export");
	if (!new_tab[0])
		return (safe_malloc(new_tab, data));
	tmp = ft_strdup(get_key_value(data->env, "PWD"));
	if (!tmp)
		return (safe_malloc(new_tab, data), free(tmp));
	new_tab[1] = ft_strdup(ft_strjoin("OLDPWD=", tmp));
	free(tmp);
	if (!new_tab[1])
		return (safe_malloc(new_tab, data));
	new_tab[2] = ft_strdup(ft_strjoin("PWD=", getcwd(cwd, PATH_MAX)));
	if (!new_tab[2])
		return (safe_malloc(new_tab, data));
	new_tab[3] = NULL;
	ft_export(data, node, new_tab);
	free_tab(new_tab);
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
