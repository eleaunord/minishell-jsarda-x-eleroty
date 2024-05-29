#include "../../../includes/minishell.h"

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

int	check_if_env_var(char *token)
{
	int	i;
	int	x;

	i = 0;
	x = ft_strlen(token); // Get the length of the token
	while (x >= 0)
	{
		if (token[x] == (char)'$') // If a dollar sign is found
			i = x;                
				// Update i to the position of the dollar sign
		x--;                       // Move to the previous character
	}
	// Check characters following the dollar sign for valid variable characters
	while (is_alpha_underscore(token[i + 1]) || token[i + 1] == '{' || token[i
		+ 1] == '?')
		i++; // Move to the next character
	// If a closing brace '}' is found, include it in the variable name
	if (token[i + 1] == '}')
		i++;
	return (i); // Return the position index
}

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
