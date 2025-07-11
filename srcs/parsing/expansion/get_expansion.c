/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:48:30 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 16:21:49 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lookup_env_value(t_env **env, char *find)
{
	t_env	*tmp;
	char	*result;

	if (!find)
		return (NULL);
	if (ft_strstr(find, "?"))
	{
		result = handle_special_case(find, g_status);
		return (result);
	}
	tmp = *env;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(find, tmp->key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*append_expanded_value(int *fag_add, char *recup, char *res,
		t_env **env)
{
	char	*tmp_content;
	char	*tmp_res;

	tmp_content = lookup_env_value(env, recup);
	if (!tmp_content)
	{
		tmp_content = ft_strdup("");
	}
	if (!res)
	{
		res = ft_strdup(tmp_content);
	}
	else
	{
		tmp_res = ft_strjoin(res, tmp_content);
		free(res);
		res = tmp_res;
	}
	free(tmp_content);
	free(recup);
	recup = NULL;
	*fag_add = 1;
	return (res);
}

static char	*init_expansion_state(int *f, int *i)
{
	*i = -1;
	*f = 0;
	return (NULL);
}

char	*perform_expansion(char *str, t_env **env, int dq, int sq)
{
	int		flag_add_to_res;
	int		i;
	char	*trim;
	char	*res;

	res = init_expansion_state(&flag_add_to_res, &i);
	while (str && str[++i])
	{
		trim = toggle_quote_flags(&sq, &dq, str, i);
		if (str[i] == '$' && sq == 0 && ++i)
		{
			trim = extract_variable_name(trim, str, &i);
			if (trim)
				res = append_expanded_value(&flag_add_to_res, trim, res, env);
		}
		else
		{
			flag_add_to_res = 1;
			res = ft_realloc(res, str[i], 0);
		}
		if (!trim && flag_add_to_res == 0)
			res = ft_realloc(res, str[i], 0);
		flag_add_to_res = 0;
	}
	return (res);
}

char	*get_expansion(char *str, t_env **env)
{
	char	*res;

	if (!str || !str[0])
		return (str);
	res = perform_expansion(str, env, 0, 0);
	free(str);
	if (ft_strcmp(res, "\"") == 0)
	{
		free(res);
		res = NULL;
	}
	if (res == NULL)
	{
		free(res);
		res = ft_strdup("");
	}
	return (res);
}
