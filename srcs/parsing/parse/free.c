#include "../../../includes/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp->cmd);
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

void	free_nodes(t_node *list)
{
	t_node	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->content)
			free(temp->content);
		if (temp->limiter_hd)
			free(temp->limiter_hd);
		if (temp->tokens_in_node)
			free_tokens(temp->tokens_in_node);
		free(temp);
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
		for (i = 0; node->args[i] != NULL; i++)
		{
			free(node->args[i]);
		}
		free(node->args);
		node->args = NULL;
	}
}
void	free_minishell(t_minishell *data, t_node *node)
{
	if (data->env)
		free_env_list(data->env);
	if (node)
	{
		free_node_cmd_args(node);
		free_nodes(node);
	}
}