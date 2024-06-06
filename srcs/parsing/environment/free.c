#include "../../../includes/minishell.h"

// void	free_tokens(t_list **nodes)
// {
// 	t_list	*current;
// 	t_token	*tok;
// 	t_token	*temp;
// 	int		i;

// 	i = 0;
// 	current = *nodes;
// 	while (current != NULL)
// 	{
// 		tok = current->tokens_in_node;
// 		while (tok != NULL)
// 		{
// 			temp = tok;
// 			tok = tok->next;
// 			free(temp->value);
// 			free(temp->cmd);
// 			i = 0;
// 			while (temp->args)
// 			{
// 				free(temp->args[i++]);
// 			}
// 			free(temp->args);
// 			free(temp->filename);
// 			free(temp->key_expansion);
// 			free(temp);
// 		}
// 		current = current->next;
// 	}
// }

void free_tokens(t_token *tokens)
{
    t_token *temp;

    while (tokens)
    {
        temp = tokens;
        tokens = tokens->next;

        free(temp->value);
        free(temp->cmd);
        if (temp->args)
        {
            for (int i = 0; temp->args[i]; i++)
            {
                free(temp->args[i]);
            }
            free(temp->args);
        }
        free(temp->filename);
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
	do
	{
		temp = list;
		list = list->next;
		free(temp->str);
		free(temp->key);
		free(temp->value);
		free(temp);
	} while (list != start);
}
/*
	Save the pointer to the next node
	Free the content of the current node
	Free the current node itself
	Move to the next node
	Set the list head to NULL to avoid dangling pointers

*/

void free_nodes(t_list *list)
{
    t_list *temp;

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
void free_minishell(t_minishell *mini)
{
    if (mini->env)
        free_env_list(mini->env);
    if (mini->nodes)
        free_nodes(mini->nodes);
}