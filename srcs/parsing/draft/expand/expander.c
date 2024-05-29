#include "../../../includes/minishell.h"

char	*expand_variables(char *token, t_minishell *mini)
{
	int		i;
	int		start;
	char	*envar;
	char	*final_str;

	i = 0;
	start = 0;
	final_str = ft_strdup(""); // Initialize final_str as an empty string
	while (token[i])
	{
		if (token[i] == '$')
		{ // If a dollar sign is found
			// If an environment variable starts here
			if (check_if_env_var(token) != 0)
				// Extract the substring from 'start' to the position before the dollar sign
				extract_substring(token, start, i, &final_str);
			// Attempt to expand the environment variable
			envar = is_envar_expansible(token, &i, &final_str, mini);
			if (envar != NULL)  // If the variable was successfully expanded
				return (envar); // Return the expanded string
			start = i + 1;
				// Update start to the position after the expanded variable
		}
		// Check if the position i is the length of the environment variable
		if (i == check_if_env_var(token))
			// Extract the substring from the position after the dollar sign to the end of the token
			extract_substring(token, i + 1, ft_strlen(token), &final_str);
		i++; // Move to the next character
	}
	return (final_str); // Return the final expanded string
}

/*
	1. Single Quotes Handling: If the token starts with a single quote,
		it trims the single quotes from the token.
	2. Non-Expandable Tokens: If the token does not contain a dollar sign ($),
		it duplicates the token as is because there are no variables to expand.
	3. Variable Expansion: If the token is expandable (contains a $),
		it calls expand_variables to replace variables with their values.
	4. Double Quotes Handling: If the token starts with a double quote,
		it trims the double quotes from the expanded string.
*/

char	*minishell_expansion(char *token, t_minishell *mini)
{
	char	*str;
	// char	*tmp;

	str = NULL;
	// if (token[0] == 39)
	// 	str = ft_strtrim(token, "\'");
	// If the token does not contain a dollar sign ($)
	if (ft_strchr(token, '$') == NULL)
		str = ft_strdup(token);
	// If str is not NULL at this point, return it (token is not expandable)
	if (str != NULL)
		return (str);
	// Expand variables in the token
	printf("%s", "check");
	str = expand_variables(token, mini);
	// // If the token starts with a double quote (")
	// if (*token == 34)
	// { // 34 is the ASCII value for double quote
	// 	tmp = str;
	// 	// Remove double quotes from the expanded string
	// 	str = ft_strtrim(str, "\"");
	// 	free(tmp);
	// 	return (str);
	// }
	return (str);
}
/*

1. Token processing loop : we iterate through each token in the linked list
2. Expand Token: It calls minishell_expansion to process and expand the current token.
3. Null Check: If the result of the expansion is NULL,
	it skips to the next token.
4. Free Original Value: It frees the memory of the original token value.
5. Empty String Check: If the expanded token is an empty string,
	it frees the memory and skips to the next token without modifying the current token.
6. Assign Expanded Value: It assigns the expanded string to the token's value.
7. Move to Next Token

*/

void	expander(t_list *nodes, t_minishell *mini)
{
	char	*temp;

	while (nodes != NULL)
	{
		// Expand the current token
		temp = minishell_expansion(nodes->content, mini);
		if (temp == NULL)
		{
			nodes = nodes->next;
			continue ;
		}
		// Free the original token value
		// free(nodes->content);
		// If the expanded token is an empty string
		if (ft_strlen(temp) == 0)
		{
			free(temp);
			// Skip to the next token without modifying the current one
			nodes = nodes->next;
			continue ;
		}
		// Assign the expanded value to the token
		nodes->content = temp;
		// Move to the next token
		nodes = nodes->next;
	}
}

