#include "../../../includes/minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	while (current != NULL)
	{
		next = current->next;
			// Store the next pointer before freeing the current node
		free(current->value); // Free the string associated with the node
		free(current);        // Free the node itself
		current = next;       // Move to the next node
	}
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
		free_env(mini->env);
	if (mini->nodes)
		free_nodes(mini->nodes);
}