#include "../../../includes/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;
	int		i;

	if (!tokens)
		return ;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp->cmd);
		free(temp->filename);
		free(temp->key_expansion);
		free(temp);
	}
}
void free_env_list(t_env *list)
{
    t_env *temp;
    t_env *start;

    start = list;
    if (!list)
        return;
    
    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp->str);
        free(temp->key);
        free(temp->value);
        free(temp);

        if (list == start)
            break;
    }
}

/*
	Save the pointer to the next node
	Free the content of the current node
	Free the current node itself
	Move to the next node
	Set the list head to NULL to avoid dangling pointers

*/

void	free_nodes(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->content)
			free(temp->content);
		if (temp->tokens_in_node)
			free_tokens(temp->tokens_in_node);
		free(temp);
	}
}
void	free_minishell(t_minishell *mini)
{
	if (mini->env)
		free_env_list(mini->env);
	if (mini->nodes)
		free_nodes(mini->nodes);
}