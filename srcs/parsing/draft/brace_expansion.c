#include "../../includes/minishell.h"

void	brace_expansion(char *token, int start, int *i, char **final_str)
{
	char	*expanded_var;
	int		end;
	char	*sub;
	char	*temp;

	if (token[*i] == '}' && token[*i - 1] != '{')
    {
		end = *i;
		sub = ft_substr(token, start, (end - start));
		expanded_var = getenv(sub);
		// free(sub);
		if (expanded_var == NULL)
			expanded_var = "";
		temp = *final_str;
		*final_str = ft_strjoin(*final_str, expanded_var);
		// free(temp);
		return ;
	}
	else
	{
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd(": bad substitution\n", STDERR_FILENO);
		return ;
	}
}

/*
	Return an error if brace expansion syntax incorrect/incomplete
=> if len = 2 then there is no closing }
=> it implies we have "${" or "${x".
*/

int	is_brace_expansion(char *token, int *i, char **final_str)
{
	int	start;
	int	len;

	len = ft_strlen(token);
	if (token[*i + 1] == '{' && len == 2)
	{
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd(": bad substitution\n", STDERR_FILENO);
		return (1);
	}
	if (token[*i + 1] == '{' && len > 2)
	{
		*i = *i + 2;
		start = *i;
		while (*i < len - 1 && is_alpha_underscore(token[*i]))
			(*i)++;
		brace_expansion(token, start, i, final_str);
		return (1);
	}
	return (0);
}
