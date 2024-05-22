#include "../../../includes/minishell.h"

void	close_quote_check(int *dq, int *sq, int *index, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		else if (c == '"' && !*sq)
			*dq = true;
		if (index)
			++(*index);
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*dq && *sq)
			*sq = false;
		else if (c == '"' && !*sq && *dq)
			*dq = false;
		if (index)
			++(*index);
	}
}

int	open_quote_check(char *line)
{
	int	double_quote;
	int	single_quote;
	int		i;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (line && line[i])
	{
		close_quote_check(&double_quote, &single_quote, &i, line[i]);
		if (line[i] && line[i] != '\'' && line[i] != '"')
			++i;
	}
	if (double_quote || single_quote)
	{
		// print_error("open quote\n"); => ?
		return (1);
	}
	return (0);
}
char	*remove_quotes(char *line)
{
	int		len;
	char	*temp_line;

	len = strlen(line);
	temp_line = (char *)malloc(len + 1);
	if (!temp_line)
	{
		fprintf(stderr, "Memory allocation error\n");
		return (NULL);
	}
	int i, j = 0;
	char quote = 0; // To keep track of the current quote character
	for (i = 0; i < len; i++)
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			if (quote == 0)
			{
				// Starting a new quote block
				quote = line[i];
			}
			else if (quote == line[i])
			{
				// Ending the current quote block
				quote = 0;
			}
			else
			{
				// Inside a different type of quote, just copy the character
				temp_line[j++] = line[i];
			}
		}
		else
		{
			// Normal character, just copy it
			temp_line[j++] = line[i];
		}
	}
	if (quote != 0)
	{
		// There was an unclosed quote
		free(temp_line);
		fprintf(stderr, "Error: Unmatched quote\n");
		return (NULL);
	}
	temp_line[j] = '\0';
	return (temp_line);
}