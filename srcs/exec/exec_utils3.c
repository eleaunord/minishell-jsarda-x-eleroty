/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:06:08 by juliensarda       #+#    #+#             */
/*   Updated: 2024/07/29 16:57:08 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_node *data)
{
	while (data)
	{
		if (data && (data->path || is_built_in(data) != -1))
		{
			if (data->error_num != 127)
			{
				waitpid(data->pid, &data->error_num, 0);
				if (WIFSIGNALED(data->error_num))
					data->error_num = WTERMSIG(data->error_num) + 128;
				else
					data->error_num = WEXITSTATUS(data->error_num);
			}
		}
		else
			wait(NULL);
		g_status = data->error_num;
		data = data->next;
	}
	if (g_status == 130)
		printf("\n");
	if (g_status == 131)
		printf("Quit (core dumped)\n");
}

char	**retrive_paths(t_minishell *shell)
{
	char	*path_value;
	char	**paths;

	path_value = get_path_value(shell, "PATH");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (freetab(paths), NULL);
	return (paths);
}

char	*retrive_path(char **paths, const char *cmd)
{
	int			i;
	struct stat	statbuf;
	char		*cmd_path;
	char		*path;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (!cmd_path)
			return (freetab(paths), NULL);
		path = ft_strjoin(cmd_path, cmd);
		free(cmd_path);
		if (!path)
			return (freetab(paths), NULL);
		if (stat(path, &statbuf) == 0 && (statbuf.st_mode & S_IXUSR))
			return (freetab(paths), path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_node *data, t_minishell *shell)
{
	char	**paths;
	char	*cmd_path;

	if (!data || !shell || !data->cmd || !data->cmd[0])
		return (NULL);
	paths = retrive_paths(shell);
	if (!paths)
	{
		if (access(data->cmd, X_OK) == 0)
			return (ft_strdup(data->cmd));
		return (NULL);
	}
	cmd_path = retrive_path(paths, data->cmd);
	if (cmd_path)
		return (cmd_path);
	if (access(data->cmd, X_OK) == 0)
		return (freetab(paths), ft_strdup(data->cmd));
	freetab(paths);
	return (NULL);
}

int	ft_lstsize_cmd(t_node *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
