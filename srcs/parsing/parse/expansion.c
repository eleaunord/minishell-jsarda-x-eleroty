#include "../../../includes/minishell.h"

void	extract_substring(char *token, int start, int end, char **final_str)
{
	char	*sub;
	char	*temp;

	// Extract the substring from token
	sub = ft_substr(token, start, (end - start));
	// Concatenate the current final_str with the new substring
	temp = *final_str;
	*final_str = ft_strjoin(*final_str, sub);
	// Free the old final_str and the temporary substring
	free(temp);
	free(sub);
}

/*

=> Check whether a char is an alphabetic char or underscore
(aka the only valid characters that can be used in environment variables)

*/
int	is_alpha_underscore(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
		return (1);
	return (0);
}
/*

1. Finding the Last $:
	- finds the position of the last occurrence of the dollar sign ($) in the token.
	- This position marks the potential start of an environment variable or special expansion sequence.

2. Identifying the End of the Variable Name:
	- Checks if the next character (token[i
		+ 1]) is an alphabetic character or an underscore.
	- Checks if the next character is an opening curly brace {,
		which might be used for variables like ${VAR}.
	- Checks if the next character is a question mark ?,
		often used in special variable expansions like $? (exit status of the last command).

3. Handle closing brace

4. Return index pointing to the last char of the var

*/


int check_env_var(char *token, int start, int *brace_end)
{
    int i;

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
            return (i); // Return the position of the closing brace
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


char *expand_variables(char *token)
{
    int i;
    int start;
    char *final_str;
    int end;
    int brace_end;

    i = 0;
    start = 0;
    final_str = ft_strdup("");
    while (token[i])
    {
        if (token[i] == '$')
        {
            start = i + 1;
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
			tok->key_expansion = expand_variables(tok->value);
		// printf("in loop %s\n", tok->key_expansion);
		tok = tok->next;
	}
	
}
