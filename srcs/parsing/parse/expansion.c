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

void	process_expansions(t_token **tokens)
{
	t_token	*tok;
	int i;

	if (!tokens)
		return ;
	tok = *tokens;
	while (tok != NULL)
	{
		if (ft_strchr(tok->value, '$') != NULL)
		{
			tok->key_expansion = expand_variables(tok->value);
			//printf("tok key expansion : %s\n", tok->key_expansion);
		}
		else
		{
			tok->key_expansion = NULL;
			//printf("tok key expansion : %s\n", tok->key_expansion);
		}
		i++;
		tok = tok->next;
	}
}


// void	set_expansions(t_token **tokens, t_node *node)
// {
// 	t_token	*tok;
// 	int i;

// 	if (!tokens || !node)
// 		return ;
// 	tok = *tokens;
// 	i = 0;
// 	while (tok != NULL)
// 	{
// 		node->key_expansion[i++] = tok->key_expansion;
// 		tok = tok->next;
// 	}
// }
// char	*expand_variables(char *token)
// {
// 	int		i;
// 	int		in_single_quotes;
// 	char	*variable;

// 	i = -1;
// 	in_single_quotes = 0;
// 	while (token[++i])
// 	{
// 		if (token[i] == '\'')
// 			in_single_quotes = !in_single_quotes;
// 		else if (token[i] == '$' && !in_single_quotes)
// 		{
// 			if (token[i + 1] == '{')
// 			{
// 				variable = extract_variables_within_braces(&token[i]);
// 				if (variable)
// 					return (variable);
// 			}
// 			else
// 			{
// 				variable = extract_variables_without_braces(&token[i]);
// 				if (variable)
// 					return (variable);
// 			}
// 		}
// 	}
// 	return (extract_variables_from_single_quotes(token));
// }
