#include "../../includes/minishell.h"

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

int	check_env_var(char *token)
{
	int	i;
	int	x;

	i = 0;
	x = ft_strlen(token);
	while (x >= 0)
	{
		if (token[x] == (char)'$')
			i = x;
		x--;
	}
	while (is_alpha_underscore(token[i + 1]) || token[i + 1] == '{' || token[i
		+ 1] == '?')
		i++;
	if (token[i + 1] == '}')
		i++;
	return (i);
}
// char	*expand_variables(char *token, t_minishell *mini)
// {
// 	int	i;
// 	int		start;
// 	char	*envar;
// 	char	*final_str;

// 	i = 0;
// 	start = 0;
// 	final_str = ft_strdup("");
// 	while (token[i])
// 	{
// 		if (token[i] == '$')
// 		{
// 			// if (check_env_var(token) != 0)
// 			// 	extract_substring(token, start, i, &final_str);
// 			envar = is_envar_expansible(token, &i, &final_str, mini);
// 			if (envar != NULL)
// 				return (envar);
// 			start = i + 1;
// 		}
// 		if (i == check_env_var(token))
//         {
//             extract_substring(token, i + 1, ft_strlen(token), &final_str);
//         }
// 		i++;
// 	}
// 	return (final_str);
// }

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

char	*get_env_value(const char *name, t_minishell *mini)
{
	t_env	*current;

	current = mini->env;
	while (current)
	{
		if (strcmp(current->key, name) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL); // Variable not found
}

char	*expand_variables(char *token, t_minishell *mini)
{
	int		i;
	int		start;
	char	*envar;
	char	*env_value;
	char	*final_str;
	char	*temp;

	i = 0;
	final_str = ft_strdup(""); // Initialize final_str with an empty string
	while (token[i])
	{
		if (token[i] == '$')
		{
			start = ++i; // Skip the '$' and mark the start of the variable name
			while (token[i] && is_alpha_underscore(token[i]))
				i++;                                   
					// Find the end of the variable name
			envar = ft_substr(token, start, i - start);
				// Extract the variable name
			env_value = get_env_value(envar, mini);    
				// Get the value of the variable
			if (env_value)
			{
				temp = ft_strjoin(final_str, env_value);
					// Append the variable value to final_str
				free(final_str);
				final_str = temp;
			}
			free(envar);
		}
		else
		{
			start = i;
			while (token[i] && token[i] != '$')
				i++;                                          
					// Find the next '$' or end of string
			temp = ft_substr(token, start, i - start);        
				// Extract the non-variable part
			char *new_final_str = ft_strjoin(final_str, temp);
				// Append it to final_str
			free(temp);
			free(final_str);
			final_str = new_final_str;
		}
	}
	return (final_str);
}

// char	*expand_variables(char *token, t_minishell *mini)
// {
// 	int	i;
// 	int		start;
// 	char	*envar;
// 	char	*final_str;

// 	i = 0;
// 	start = 0;
// 	final_str = ft_strdup("");
// 	while (token[i])
// 	{
// 		if (token[i] == '$')
// 		{
//            
	// Check if it an actual environment variable and if we can expand it
//             // expand the environment vairable
// 		}
// 		i++;
// 	}
// 	return (final_str);
// }
void	call_expander(t_list *list, t_minishell *data)
{
	t_list	*current_node;
	t_token	*token;

	// (void)data;
	current_node = list;
	while (current_node)
	{
		token = (t_token *)current_node->tokens_in_node;
		while (token)
		{
			if (ft_strchr(token->value, '$') != NULL)
				token->value = expand_variables(token->value, data);
			else
				token->value = token->value; // remains unchanged

            printf("%s\n", token->value);
			token = token->next;
		}
		current_node = current_node->next;
	}
}
