#include "../../../includes/minishell.h"

int is_only_tabs(char *str)
{
	while (*str)
	{
		if (*str != '\t')
		{
			return 0;
		}
		str++;
	}
	return 1;
}
int	is_space(char *line)
{
	int	a;

	a = 0;
	while (line[a] == ' ' || line[a] == '\t' || line[a] == '\n')
		a += 1;
	if (line[a] == '\0')
		return (1);
	return (0);
}

int check_line(char **line)
{
	if ((*line)[0] == '\0' || is_space(*line) || ft_strncmp(*line, "\n", 0))
		return 1;
	return 0;
}
bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_alpha_underscore(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
		return (1);
	return (0);
}
