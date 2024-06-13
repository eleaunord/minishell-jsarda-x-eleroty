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
// ft_strsub definition
char *ft_strsub(const char *s, unsigned int start, size_t len)
{
    char *sub;
    size_t i;

    // Check for null pointer
    if (!s)
        return NULL;

    // Allocate memory for the substring (+1 for null terminator)
    sub = (char *)malloc(sizeof(char) * (len + 1));
    if (!sub)
        return NULL;

    // Copy the substring
    i = 0;
    while (i < len)
    {
        sub[i] = s[start + i];
        i++;
    }

    // Null-terminate the new string
    sub[len] = '\0';

    return sub;
}

char *expand_variables(char *token)
{
    int i;
    int start;
    char *final_str;
    int end;
    //int brace_end;
    int in_single_quotes;

    i = 0;
    final_str = ft_strdup("");
    if (!final_str)
        return NULL;
    in_single_quotes = 0;
	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
	{
		free(final_str);
		return (NULL);
	}
    while (token[i])
    {
        if (token[i] == '\'')
            in_single_quotes = !in_single_quotes;
        else if (token[i] == '$' && !in_single_quotes)
        {
            start = i;
            if (token[start + 1] == '{')
            {
                // Find the closing brace
                end = start + 2;
                while (token[end] && token[end] != '}')
                    end++;
                if (token[end] == '}')
                {
                    // Include the closing brace
                    end++;
                    // Extract the variable including the $ and braces
                    free(final_str);
                    final_str = ft_strsub(token, start, end - start);
                    if (!final_str)
                        return NULL;
                    return final_str; // Return immediately after extracting
                }
            }
            else
            {
                // Handle variables without braces
                end = start + 1;
                while (token[end] && (is_alpha_underscore(token[end]) || token[end] == '?'))
                    end++;
                // Extract the variable including the $
                free(final_str);
                final_str = ft_strsub(token, start, end - start);
                if (!final_str)
                    return NULL;
                return final_str; // Return immediately after extracting
            }
        }
        i++;
    }
    // If no variable found, return the original string duplicated
    free(final_str);
    return ft_strdup(token);
}

void	process_expansions(t_token **tokens, t_node *node)
{
	t_token	*tok;

    if (!tokens || !node) // Check for null tokens and node
        return;

    tok = *tokens;
	while (tok != NULL)
	{
		if (ft_strchr(tok->value, '$') != NULL)
		{
			node->key_expansion = expand_variables(tok->value);
			tok->key_expansion = node->key_expansion;
		}
		if (!node->key_expansion)
		{
			node->key_expansion = NULL;
			tok->key_expansion = NULL;
		}
		tok = tok->next;
	}
		// t_node *head = node;
	// while (head)
	// {

	// 	printf("EXPANSION: %s\n", head->key_expansion);

	// 	head = head->next;
	// }
}

