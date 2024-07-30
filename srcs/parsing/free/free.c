/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:50:25 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 12:51:49 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value)
		{
			free(temp->value);
		}
		if (temp->cmd)
			free(temp->cmd);
		if (temp->key_expansion)
			free(temp->key_expansion);
		free(temp);
	}
}

void	free_env_list(t_env *list)
{
	t_env	*temp;
	t_env	*start;

	start = list;
	if (!list)
		return ;
	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp->str);
		free(temp->key);
		free(temp->value);
		free(temp);
		if (list == start)
			break ;
	}
}

void	free_node_cmd_args(t_node *node)
{
	int	i;

	if (node == NULL)
		return ;
	if (node->cmd)
	{
		free(node->cmd);
		node->cmd = NULL;
	}
	if (node->args)
	{
		i = 0;
		while (node->args[i] != NULL)
		{
			free(node->args[i]);
			node->args[i] = NULL;
			i++;
		}
		free(node->args);
		node->args = NULL;
	}
}

void	freelist(t_node **nodes)
{
	t_node	*current;
	t_node	*next;

	if (!nodes || !*nodes)
		return ;
	current = *nodes;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*nodes = NULL;
}

void	free_mini(t_minishell *data)
{
	if (data->env)
		free_env_list(data->env);
	if (data->env_dup)
		free_env_list(data->env_dup);
	free(data);
}
