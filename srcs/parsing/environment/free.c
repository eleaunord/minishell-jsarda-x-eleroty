#include "../../../includes/minishell.h"

void	free_env_list(t_env *list)
{
	t_env	*start;
	t_env	*temp;

	start = list;
	if (!list)
		return ;
	do
	{
		temp = list;
		list = list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	} while (list != start);
}

void	free_nodes(t_list **tokens_list)
{
	t_list	*current;
	t_list	*next;

	if (tokens_list == NULL || *tokens_list == NULL)
	{
		return ;
	}
	current = *tokens_list;
	while (current != NULL)
	{
		next = current->next;   // Save the pointer to the next node
		free(current->content); // Free the content of the current node
		free(current);          // Free the current node itself
		current = next;         // Move to the next node
	}
	*tokens_list = NULL; // Set the list head to NULL to avoid dangling pointers
}

void	free_minishell(t_minishell *mini)
{
	if (mini->env)
		free_env_list(mini->env);
	if (mini->nodes)
		free_nodes(&mini->nodes);
}