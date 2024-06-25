/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:27:07 by jsarda            #+#    #+#             */
/*   Updated: 2024/06/19 14:52:05 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd_path(char *cmd, t_minishell *data)
{
	char		*path_value;
	char		**paths;
	int			i;
	struct stat	statbuf;
	char		*path;
	char		*cmd_path;

	if (!cmd || !data)
		return (NULL);
	path_value = get_path_value(data, "PATH");
	if (!path_value)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	paths = ft_split(path_value, ':');
	if (!paths)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (!cmd_path)
			return (free_split(paths), NULL);
		path = ft_strjoin(cmd_path, cmd);
		free(cmd_path);
		if (!path)
			return (free_split(paths), NULL);
		if (stat(path, &statbuf) == 0 && (statbuf.st_mode & S_IXUSR))
			return (free_split(paths), path);
		free(path);
		i++;
	}
	if (access(cmd, X_OK) == 0)
		return (free_split(paths), cmd);
	return (free_split(paths), NULL);
}
