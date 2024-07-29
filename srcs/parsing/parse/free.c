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
void free_node_cmd_args(t_node *node)
{
	if (node == NULL)
		return;

	if (node->cmd)
	{
		free(node->cmd);
		node->cmd = NULL;
	}

	if (node->args)
	{
		int i = 0;
		while (node->args[i] != NULL)
		{
			free(node->args[i]);
			node->args[i] = NULL; // Always good to NULL out freed pointers
			i++;
		}
		free(node->args);
		node->args = NULL;
	}
}
void freelist(t_node **nodes)
{
    t_node *current;
    t_node *next;

    if (!nodes || !*nodes)
        return;

    current = *nodes;
    while (current != NULL)
    {
        next = current->next;
        free(current->content);  // Free the content string
        free(current);           // Free the node itself
        current = next;
    }

    *nodes = NULL;  // Set the head pointer to NULL to avoid dangling pointer
}

void free_nodes(t_node *head)
{
	t_node *current = head;
	t_node *next;

	if (head == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if(current->args)
			freetab(current->args);
		if (current->content)
			free(current->content);
		if (current->limiter_hd)
			free(current->limiter_hd);
		if (current->filename_out)
			free(current->filename_out);
		if (current->filename_in)
			free(current->filename_in);
		if (current->tokens_in_node)
			free_tokens(current->tokens_in_node);
		free(current);
		current = next;
	}
}
void free_mini(t_minishell *data)
{
	if (data->env)
		free_env_list(data->env);
	if (data->env_dup)
		free_env_list(data->env_dup);
	free(data);
}
void	free_minishell(t_minishell *data, t_node *node)
{
	if (data->env)
		free_env_list(data->env);
	if (data->env_dup)
		free_env_list(data->env_dup);
	if (node)
	{
		free_nodes(node);
	}
}
