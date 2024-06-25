#include "../../../includes/minishell.h"

char *extract_variables_within_braces(const char *token)
{
	int start;
	int end;

	start = 0;
	end = start + 1;
	while (token[end] && token[end] != '}')
	{
		end++;
	}
	if (token[end] == '}')
	{
		end++;
		return ft_strsub(token, start, end - start);
	}
	return NULL;
}

char *extract_variables_without_braces(const char *token)
{
	int start;
	int end;

	start = 0;
	end = start + 1;
	while (token[end] && (is_alpha_underscore(token[end]) || token[end] == '?'))
		end++;
	return ft_strsub(token, start, end - start);
}

char *extract_variables_from_single_quotes(const char *token)
{
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
	{
		return NULL;
	}
	return ft_strdup(token);
}

char *expand_variables(char *token)
{
	int i;
	int in_single_quotes;
	char *variable = NULL;
	char *leading_spaces = NULL;
	char *trailing_spaces = NULL;
	char *result = NULL;

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
			{
				// Preserve leading spaces
				leading_spaces = ft_strsub(token, 0, i);
				// Preserve trailing spaces
				trailing_spaces = ft_strsub(token, i + ft_strlen(variable), ft_strlen(token) - (i + ft_strlen(variable)));
				// Construct the final result with leading spaces, variable, and trailing spaces
				result = (char *)malloc(ft_strlen(leading_spaces) + ft_strlen(variable) + ft_strlen(trailing_spaces) + 1);
				if (result)
				{
					strcpy(result, leading_spaces);
					strcat(result, variable);
					strcat(result, trailing_spaces);
				}
				free(leading_spaces);
				free(trailing_spaces);
				free(variable);
				return result;
			}
		}
	}
	return extract_variables_from_single_quotes(token);
}


void check_needs_expansion(t_token *tok, int *needs_expansion)
{
	char *value = tok->value;
	*needs_expansion = 0;

	while (*value)
	{
		if (*value == '$' && is_alpha_underscore(*(value + 1)))
		{
			*needs_expansion = 1;
			break;
		}
		value++;
	}
}

void process_expansions(t_token **tokens)
{
	t_token *tok;
	int needs_expansion;

	if (!tokens)
		return;

	tok = *tokens;
	while (tok != NULL)
	{
		check_needs_expansion(tok, &needs_expansion);

		if (needs_expansion)
			tok->key_expansion = expand_variables(tok->value);
		else
			tok->key_expansion = NULL;

		tok = tok->next;
	}
}
