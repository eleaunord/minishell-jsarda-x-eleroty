#include "../../../includes/minishell.h"

int	is_alpha_underscore(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
		return (1);
	return (0);
}

int	check_env_var(char *token, int start, int *brace_end)
{
	int	i;

	i = start;
	*brace_end = 0; // Initialize brace_end to 0
	if (token[i] == '{')
	{
		i++;
		while (is_alpha_underscore(token[i]) || token[i] == '?')
			i++;
		if (token[i] == '}')
		{
			*brace_end = 1; // Mark that there was a closing brace
			return (i);     // Return the position of the closing brace
		}
		else
			return (0); // Invalid syntax
	}
	else
	{
		while (is_alpha_underscore(token[i]) || token[i] == '?')
			i++;
		return (i - 1); // Return the last character index of the variable name
	}
}

void	extract_substring(char *token, int start, int end, char **final_str)
{
	char	*sub;
	char	*temp;

	if (start >= end || token[start] == '\0')
	{
		return ;
	}
	// Extract the substring from token
	sub = ft_substr(token, start, (end - start));
	if (!sub)
		return ;
	// Concatenate the current final_str with the new substring
	temp = *final_str;
	*final_str = ft_strjoin(*final_str, sub);
	// Free the old final_str and the temporary substring
	free(temp);
	free(sub);
}

char	*expand_variables(char *token)
{
	int		i;
	int		start;
	char	*final_str;
	int		end;
	int		brace_end;
	int		in_single_quotes;
	char	temp[2];
	char	*old_final_str;

	i = 0;
	start = 0;
	final_str = ft_strdup("");
	if (!final_str)
		return (NULL);
	in_single_quotes = 0;
	// Check if the token is entirely enclosed in single quotes
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
	{
		free(final_str);
		return (NULL);
	}
	while (token[i])
	{
		if (token[i] == '\'')
		{
			in_single_quotes = !in_single_quotes;
		}
		else if (token[i] == '$' && !in_single_quotes)
		{
			start = i + 1;
			// Check if the character after $ is valid for variable expansion
			if (token[start] == '{' || is_alpha_underscore(token[start])
				|| token[start] == '?')
			{
				end = check_env_var(token, start, &brace_end);
				if (end != 0)
				{
					if (brace_end)
					{
						// Skip the '{' at start and '}' at end
						extract_substring(token, start + 1, end, &final_str);
					}
					else
					{
						// Extract the variable name directly
						extract_substring(token, start, end + 1, &final_str);
					}
					i = end; // Move i to the end of the variable name
				}
			}
			else
			{
				free(final_str);
				return (NULL);
			}
		}
		else
		{
			temp[0] = token[i];
			temp[1] = '\0';
			old_final_str = final_str;
			final_str = ft_strjoin(final_str, temp);
			if (!final_str)
			{
				free(old_final_str);
				return (NULL);
			}
			free(old_final_str);
		}
		i++;
	}
	return (final_str);
}

void	process_expansions(t_token **tokens)
{
	t_token	*tok;

	if (!tokens || !*tokens)
		return ;
	tok = *tokens;
	while (tok)
	{
		if (ft_strchr(tok->value, '$') != NULL)
		{
			tok->key_expansion = expand_variables(tok->value);
		}
		if (!tok->key_expansion || !*(tok->key_expansion))
			tok->key_expansion = NULL;
		tok = tok->next;
	}
}
