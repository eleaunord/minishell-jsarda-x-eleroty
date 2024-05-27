#include "../../../includes/minishell.h"

char	*expand_variables(char *token)
{
	int		i;
	int		start;
	char	*envar;
	char	*final_str;

	i = 0;
	start = 0;
	final_str = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '$')
		{
			if (check_env_var(token) != 0)
				extract_substring(token, start, i, &final_str);
			envar = is_envar_expansible(token, &i, &final_str);
			if (envar != NULL)
				return (envar);
			start = i + 1;
		}
		if (i == check_env_var(token))
			extract_substring(token, i + 1, ft_strlen(token), &final_str);
        i++;
	}
	return (final_str);
}
static int	in_substring(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && in_substring(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && in_substring(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}

char	*minishell_expansion(char *token)
{
	char	*str;

	str = NULL;
	if (token[0] == "\'")
		str = ft_strtrim(token, "\'");
	if (ft_strchr(token, '$') == NULL)
		str = ft_strdup(token);
	if (str != NULL) // aka non expensible 
		return (str);
	str = expand_variables(token);
    //
	if (*token == 34)
		return (ft_strupdate(&str, ft_strtrim(str, "\"")), str);
	return (str);
}
void	expander(t_token *token)
{
	char	*temp;

	while (token != NULL)
	{
		temp = minishell_expansion(token->value);
		if (temp == NULL)
		{
			token = token->next;
			continue ;
		}
		free(token->value); // ?
		if (ft_strlen(temp) == 0)
		{
			free(temp);
			// Handling empty case, skip the token without deleting
			token = token->next;
			continue ;
		}
		token->value = temp;
		token = token->next;
	}
}
