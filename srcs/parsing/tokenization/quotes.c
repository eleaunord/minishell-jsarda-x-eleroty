#include "../../../includes/minishell.h"

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