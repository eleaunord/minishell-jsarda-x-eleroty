#include "../../../includes/minishell.h"

// Helper function to create a new list node
t_list	*create_node(char *token)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	new_node->content = strdup(token);
	new_node->next = NULL;
	return (new_node);
}

// Helper function to add a node to the end of the linked list
void	append_node(t_list **tokens_list, char *token)
{
	t_list	*new_node;
	t_list	*current;

	new_node = create_node(token);
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

// Function to trim leading and trailing spaces from a string
char	*trim_whitespace(char *str)
{
	char	*end;

	// Trim leading space
	while (isspace((unsigned char)*str))
		str++;
	if (*str == 0) // All spaces?
		return (str);
	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;
	// Write new null terminator character
	end[1] = '\0';
	return (str);
}

// Function to collapse multiple spaces into a single space
char	*collapse_spaces(char *str)
{
	char	*dst;
	char	*src;
	int		space;

	dst = str;
	src = str;
	space = 0;
	while (*src != '\0')
	{
		if (isspace((unsigned char)*src))
		{
			if (!space)
			{
				*dst++ = ' ';
				space = 1;
			}
		}
		else
		{
			*dst++ = *src;
			space = 0;
		}
		src++;
	}
	*dst = '\0';
	return (str);
}

// Main function to trim spaces and store tokens in the linked list
void	ft_split_pipes_spaces(char *line, t_list **tokens_list)
{
	char *start;
	char *pipe_pos;
	char *segment;

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
}