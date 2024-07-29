/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:02:40 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/29 09:41:48 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(t_node *data)
{
	while (data)
	{
		if (data->fdin != -1 && data->fdin != 0)
			close(data->fdin);
		if (data->fdout != -1 && data->fdout != 1)
		{
			if (data->next && data->next->fdout != data->fdout)
				return ;
			close(data->fdout);
		}
		data = data->next;
	}
}

void	free_hd_file(t_node **data, int mode)
{
	t_node	*tmp_data;

	tmp_data = *data;
	while (tmp_data)
	{
		if (mode == 1 && tmp_data->is_hd)
		{
			if (tmp_data->tmpfile_hd)
				free(tmp_data->tmpfile_hd);
			tmp_data->tmpfile_hd = NULL;
		}
		else if (mode == 2 && tmp_data->is_hd && tmp_data->tmpfile_hd)
			unlink(tmp_data->tmpfile_hd);
		tmp_data = tmp_data->next;
	}
}

void	free_child(t_node *data, t_shell *shell, int exit_status)
{
	ft_free_env_list(&(shell->envp));
	ft_free_env_list(&(shell->exp));
	free(data->path);
	data->path = NULL;
	free_hd_file(&data, 1);
	ft_close_fd(data);
	ft_clear_datas(&(shell->datas));
	free(shell);
	exit(exit_status);
}

void	ft_recup(t_shell *shell)
{
	static t_shell	*tmp_shell;

	if (shell)
		tmp_shell = shell;
	else
	{
		ft_free_env_list(&(tmp_shell->envp));
		ft_free_env_list(&(tmp_shell->exp));
		ft_clear_datas(&(tmp_shell->datas));
		free(tmp_shell);
	}
}

void	freetab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}
