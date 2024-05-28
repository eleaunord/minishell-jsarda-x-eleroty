#include "../../../includes/minishell.h"


int	ft_strchr_index(const char *s, int c)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}
char	*ft_stop_chr(char *str, char c)
{
	int		i;
	char	*dest;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			dest = ft_calloc(i + 2, sizeof(char));
			dest = ft_memcpy(dest, str, i + 1);
			return (dest);
		}
		i++;
	}
	return (str);
} 

/*
Check for '?' in Token

	1. Handling Single Character Token:
		-> If the length of the token is 2 (indicating only the '?' character and one more character),
	it directly replaces the token with the current exit status mini->exit.

	2. Finding the substring
		->  It identifies the substring to be replaced by searching for alphanumeric characters after the '?' character
		until a non-alphanumeric character is encountered.

	3. Expanding the Status Code
		-> converts the exit status to a string using ft_itoa.

	4. Constructs expanded string by concatenating the status code with the substring following the '?'.
*/

int	handle_single_char_token(char **final_str, t_minishell *mini)
{
	char	*tmp;

	tmp = *final_str;
	*final_str = ft_itoa(mini->exit);
	free(tmp);
	return (1);
}
int	cmd_exit_status(char *token, int start, int *i, char **final_str,
		t_minishell *mini)
{
	char	*sub;
	char	*expanded_var;
	char	*temp;
	int		i;

	if (ft_strchr(token, '?') != NULL)
	{
		start = ft_strchr_index(token, '?');
		if (ft_strlen(token) == 2)
			return (handle_single_char_token(final_str, mini));
		i = 0;
		while (is_alpha_underscore(token[*i + 1]))
			*i += 1;
		sub = ft_substr(token, start + 1, (*i - start));
		expanded_var = ft_itoa(mini->exit);
		temp = *final_str;
		*final_str = ft_strjoin(ft_itoa(mini->exit), sub);
		free(temp);
		free(sub);
		free(expanded_var);
		return (1);
	}
	return (0);
}
/*
Get the value of the environment var corresponding to the extracted name


*/
char	*get_env(char *sub, t_minishell *mini)
{
	t_env	*env_list;
	char	*temp;

	env_list = mini->env;
	while (env_list)
	{
		temp = ft_stop_chr((char *)env_list->value, '=');
		if (!ft_strncmp(sub, temp, ft_strlen(sub)))
		{
			free(temp);
			return (ft_strchr((char *)env_list->value, '=') + 1);
		}
		env_list = env_list->next;
		free(temp);
	}
	return (NULL);
}
/*

Handles the expansion of the next character in the token,
	determining if it is part of :
	- a brace expansion,
	- a regular environment variable,
	- a special character like ?.

ELSE extract var name from token and  appends the expanded variable to the final_str.
If the variable is not found, an empty string is used instead.

Updates *final_str accordingly.
*/

void	proceeds_expansion(char *token, int *i, char **final_str,
		t_minishell *mini)
{
	int		start;
	char	*sub;
	char	*expanded_var;
	char	*temp;

	start = *i;
	while (is_alpha_underscore(token[*i + 1]))
		(*i)++;
	if (cmd_exit_status(token, start, i, final_str, mini) == 1)
		return ;
	sub = ft_substr(token, (start + 1), (*i - start));
	expanded_var = get_env(sub, mini);
	free(sub);
	if (expanded_var == NULL)
		expanded_var = "";
	temp = *final_str;
	*final_str = ft_strjoin(*final_str, expanded_var);
	free(temp);
}

void	append_dollar_sign(char **final_str)
{
	char	*temp;

	temp = *final_str;
	*final_str = ft_strjoin(*final_str, "$");
	free(temp);
}

int	is_btwn_single_quotes(char *token)
{
	if (token[0] == 39)
		return (1);
	return (0);
}

char	*is_envar_expansible(char *token, int *i, char **final_str)
{
	int		start;
	int		end;
	char	*sub;

	if (is_btwn_single_quotes(*final_str) == 0)
	{
		if (is_brace_expansion(token, i, final_str) == 1)
			return (NULL);
		if (is_alpha_underscore(token[*i + 1]) || token[*i + 1] == '?')
			proceed_expansion(token, i, final_str);
		else
			append_dollar_sign(final_str);
	}
	else
	{
		start = *i;
		while (is_alpha_underscore(token[*i + 1]))
			*i += 1;
		end = *i;
		sub = ft_substr(token, start, (end - start + 1));
		return (sub);
	}
	return (NULL);
}
