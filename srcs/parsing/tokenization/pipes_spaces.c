#include "../../../includes/minishell.h"

t_node *create_node(char *token)
{
	t_node *new_node;

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

void append_node(t_node **tokens_list, char *token)
{
	t_node *new_node;
	t_node *current;

	new_node = create_node(token);
	if (!new_node)
	{
		return; // If new_node creation failed, return immediately
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

void process_segment(char *start, t_node **tokens_list)
{
	char *segment;

	segment = trim_whitespace(start);
	segment = collapse_spaces(segment);
	append_node(tokens_list, segment);
}

void split_line(char *line, t_node **tokens_list)
{
	char *start;
	char *current;
	bool in_single_quote;
	bool in_double_quote;

	start = line;
	current = line;
	in_single_quote = false;
	in_double_quote = false;
	while (*current != '\0')
	{
		if (*current == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*current == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*current == '|' && !in_single_quote && !in_double_quote)
		{
			*current = '\0';
			process_segment(start, tokens_list);
			start = current + 1;
		}
		current++;
	}
	process_segment(start, tokens_list);
}

void ft_split_pipes_spaces(char *line, t_node **tokens_list)
{
	*tokens_list = NULL;
	split_line(line, tokens_list);
	return ;
}
