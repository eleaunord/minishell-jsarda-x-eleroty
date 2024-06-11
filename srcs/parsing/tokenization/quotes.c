#include "../../../includes/minishell.h"

void	close_quote_check(int *dq, int *sq, int *index, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = 1;
		else if (c == '"' && !*sq)
			*dq = 1;
		if (index)
			++(*index);
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*dq && *sq)
			*sq = 0;
		else if (c == '"' && !*sq && *dq)
			*dq = 0;
		if (index)
			++(*index);
	}
}

int	open_quote_check(char *line)
{
	int	double_quote;
	int	single_quote;
	int	i;

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

void toggle_quote_status(char c, char *quote)
{
    if (c == '"' || c == '\'')
    {
        if (*quote == 0)
            *quote = c;
        else if (*quote == c)
            *quote = 0;
    }
}

void copy_without_quotes(const char *line, char *temp_line)
{
    int i = 0;
    int j = 0;
    char quote = 0;
    int len = strlen(line);

    while (i < len)
    {
        toggle_quote_status(line[i], &quote);
        if (quote == 0 || (line[i] != '"' && line[i] != '\''))
            temp_line[j++] = line[i];
        i++;
    }
    temp_line[j] = '\0';
}

char *remove_quotes(const char *line)
{
    int len;
    char *temp_line;

    if (!line)
        return NULL;

    len = strlen(line);
    temp_line = (char *)malloc(len + 1);
    if (!temp_line)
        return NULL;

    copy_without_quotes(line, temp_line);

    return temp_line;
}
