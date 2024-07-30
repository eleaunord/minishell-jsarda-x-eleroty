/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:02:40 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/30 14:35:29 by eleroty          ###   ########.fr       */
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
		if (mode == 1 && tmp_data->is_here_doc)
		{
			if (tmp_data->last_heredoc)
				free(tmp_data->last_heredoc);
			tmp_data->last_heredoc = NULL;
		}
		else if (mode == 2 && tmp_data->is_here_doc && tmp_data->last_heredoc)
			unlink(tmp_data->last_heredoc);
		tmp_data = tmp_data->next;
	}
}

void	free_child(t_node *data, t_minishell *shell, int exit_status)
{
	ft_free_env_list(&(shell->env));
	ft_free_env_list(&(shell->env_dup));
	free(data->path);
	data->path = NULL;
	free_hd_file(&data, 1);
	ft_close_fd(data);
	clear_nodes(&(shell->nodes));
	free(shell);
	exit(exit_status);
}

void	ft_recup(t_minishell *shell)
{
	static t_minishell	*tmp_shell;

	if (shell)
		tmp_shell = shell;
	else
	{
		ft_free_env_list(&(tmp_shell->env));
		ft_free_env_list(&(tmp_shell->env_dup));
		clear_nodes(&(tmp_shell->nodes));
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
		{
			free(tab[i]);
		}
		i++;
	}
	free(tab);
}
