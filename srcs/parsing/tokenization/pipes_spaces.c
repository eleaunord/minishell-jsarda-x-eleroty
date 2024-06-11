#include "../../../includes/minishell.h"

// Helper function to create a new list node
t_node	*create_node(char *token)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node)); // LEAK HERE
	if (!new_node)
	{
		exit(EXIT_FAILURE);
	}
	new_node->content = ft_strdup(token); // LEAK HERE
    if (!new_node->content)
    {
        free(new_node); 
        exit(EXIT_FAILURE);
    }
	new_node->next = NULL;
	return (new_node);
}

// Helper function to add a node to the end of the linked list
void	append_node(t_node **tokens_list, char *token)
{
	t_node	*new_node;
	t_node	*current;

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

// Function to trim leading and trailing spaces from a string,
	//ignoring spaces inside quotes
char	*trim_whitespace(char *str)
{
	char	*end;
	bool	in_quote;
	char	quote_char;

	in_quote = false;
	quote_char = '\0';
	// Trim leading space
	while (*str && isspace((unsigned char)*str))
		str++;
	if (*str == 0) // All spaces?
		return (str);
	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str)
	{
		if (*end == '\'' || *end == '"')
		{
			if (in_quote && *end == quote_char)
			{
				in_quote = false;
				quote_char = '\0';
			}
			else if (!in_quote)
			{
				in_quote = true;
				quote_char = *end;
			}
		}
		if (!in_quote && isspace((unsigned char)*end))
			end--;
		else
			break ;
	}
	// Write new null terminator character
	end[1] = '\0';
	return (str);
}

// Function to collapse multiple spaces into a single space,
	//ignoring spaces inside quotes
char	*collapse_spaces(char *str)
{
	char	*dst;
	char	*src;
	bool	in_quote;
	char	quote_char;
	int		space;

	in_quote = false;
	quote_char = '\0';
	space = 0;
	dst = str;
	src = str;
	while (*src != '\0')
	{
		if (*src == '\'' || *src == '"')
		{
			if (in_quote && *src == quote_char)
			{
				in_quote = false;
				quote_char = '\0';
			}
			else if (!in_quote)
			{
				in_quote = true;
				quote_char = *src;
			}
			*dst++ = *src;
		}
		else if (isspace((unsigned char)*src))
		{
			if (!in_quote)
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

// Main function to trim spaces and store tokens in the linked list,
	//preserving spaces inside quotes
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
