/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:27:07 by jsarda            #+#    #+#             */
/*   Updated: 2024/05/29 14:16:10 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd_path(char *cmd, t_minishell *data)
{
	char		*path_value;
	char		**paths;
	int			i;
	struct stat	*statbuf;
	char		*path;
	char		*cmd_path;

	statbuf = NULL;
	if (!cmd || !data)
		return (NULL);
	path_value = get_path_value(data, "PATH");
	if (!path_value)
		return (NULL);
	printf("hello\n");
	paths = ft_split(path_value, ':');
	//free(path_value);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (!cmd_path)
			return (free_split(paths), NULL);
		path = ft_strjoin(cmd_path, cmd);
		printf("path : %s\n", path);
		free(cmd_path);
		if (!path)
			return (free_split(paths), NULL);
		if (stat(path, statbuf) == 0)
			return (free_split(paths), path);
		free(path);
		i++;
	}
	return (free_split(paths), NULL);
}
