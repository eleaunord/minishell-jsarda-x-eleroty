#include "../../../includes/minishell.h"

int	check_env_var(char *token, int start, int *brace_end)
{
	int	i;

	i = start;
	*brace_end = 0;
	if (token[i] == '{')
	{
		i++;
		while (is_alpha_underscore(token[i]) || token[i] == '?')
			i++;
		if (token[i] == '}')
		{
			*brace_end = 1;
			return (i);
		}
		else
			return (0);
	}
	else
	{
		while (is_alpha_underscore(token[i]) || token[i] == '?')
			i++;
		return (i - 1);
	}
}

char	*extract_variables_within_braces(const char *token)
{
	int	start;
	int	end;

	start = 0;
	end = start + 1;
	while (token[end] && token[end] != '}')
	{
		end++;
	}
	if (token[end] == '}')
	{
		end++;
		return (ft_strsub(token, start, end - start));
	}
	return (NULL);
}

char	*extract_variables_without_braces(const char *token)
{
	int	start;
	int	end;

	start = 0;
	end = start + 1;
	while (token[end] && (is_alpha_underscore(token[end]) || token[end] == '?'))
		end++;
	return (ft_strsub(token, start, end - start));
}

char	*extract_variables_from_single_quotes(const char *token)
{
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
	{
		return (NULL);
	}
	return (ft_strdup(token));
}

char	*expand_variables(char *token)
{
	int		i;
	int		in_single_quotes;
	char	*variable;

	i = -1;
	in_single_quotes = 0;
	while (token[++i])
	{
		if (token[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (token[i] == '$' && !in_single_quotes)
		{
			if (token[i + 1] == '{')
				variable = extract_variables_within_braces(&token[i]);
			else
				variable = extract_variables_without_braces(&token[i]);
            if (variable)
				return (variable);
		}
	}
	return (extract_variables_from_single_quotes(token));
}

void process_expansions(t_token **tokens)
{
    t_token *tok;

    if (!tokens)
        return;

    tok = *tokens;
    while (tok != NULL)
    {
        int needs_expansion = 0;
        char *value = tok->value;
        
        while (*value)
        {
            if (*value == '$' && is_alpha_underscore(*(value + 1)))
            {
                needs_expansion = 1;
                break;
            }
            value++;
        }

        if (needs_expansion)
        {
            tok->key_expansion = expand_variables(tok->value);
        }
        else
        {
            tok->key_expansion = NULL;
        }

        tok = tok->next;
    }
}
