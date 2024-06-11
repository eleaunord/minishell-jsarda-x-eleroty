#include "../../../includes/minishell.h"

t_node	*create_node(char *token)
{
	t_node	*new_node;

	new_node = (t_node *)calloc(1, sizeof(t_node));
	// Use calloc instead of malloc
	if (!new_node)
	{
		exit(EXIT_FAILURE);
	}
	new_node->content = ft_strdup(token);
	if (!new_node->content)
	{
		free(new_node); // Free the node if strdup fails
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	return (new_node);
}

void	append_node(t_node **tokens_list, char *token)
{
	t_node	*new_node;
	t_node	*current;

	new_node = create_node(token);
	if (!new_node)
	{
		return ; // If new_node creation failed, return immediately
	}
	if (*tokens_list == NULL)
	{
		*tokens_list = new_node;
	}
	else
	{
		current = *tokens_list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

// Main function to trim spaces and store tokens in the linked list,
// preserving spaces inside quotes
char	*ft_split_pipes_spaces(char *line, t_node **tokens_list)
{
	char	*start;
	char	*pipe_pos;
	char	*segment;

	*tokens_list = NULL; // Initialize the linked list
	start = line;
	while ((pipe_pos = strchr(start, '|')) != NULL)
	{
		// Extract the segment before the pipe symbol
		*pipe_pos = '\0';
		segment = trim_whitespace(start);
		segment = collapse_spaces(segment);
		append_node(tokens_list, segment);
		// Move to the next segment after the pipe symbol
		start = pipe_pos + 1;
	}
	// Process the last segment
	segment = trim_whitespace(start);
	segment = collapse_spaces(segment);
	append_node(tokens_list, segment);
	return (line);
}
