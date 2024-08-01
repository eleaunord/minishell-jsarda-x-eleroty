/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:01:01 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 12:17:51 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_content_env(t_env **env, char *find)
{
	t_env	*tmp;
	 // char *expanded_value;

	if (!find)
	{
		printf("get_content_env: find is NULL\n");
		return (NULL);
	}
	if (ft_strcmp(find, "?") == 0)
	{
		return (ft_itoa(g_status));
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

int	valid_name(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| c == '?')
		return (1);
	return (0);
}

char	*reallocator(char *res, char c, int i)
{
	char	*cpy;

	cpy = NULL;
	if (!res)
	{
		res = malloc(2);
		res[0] = c;
		res[1] = 0;
		return (res);
	}
	if (res)
	{
		cpy = ft_strdup(res);
		free(res);
	}
	res = malloc(sizeof(char) * (ft_strlen(cpy) + 2));
	while (cpy && cpy[i])
	{
		res[i] = cpy[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = 0;
	free(cpy);
	return (res);
}

char	*recup_dq_sq_expander(char *str, int i, int *sq, int *dq)
{
	if (str[i] == '\'' && *sq == 0 && *dq == 1)
		;
	else if (str[i] == '\'' && *sq == 0 && *dq == 0)
		*sq = 1;
	else if (str[i] == '\'' && *sq == 1)
		*sq = 0;
	else if (str[i] == '\"' && *dq == 0 && *sq == 1)
		;
	else if (str[i] == '\"' && *dq == 0 && *sq == 0)
		*dq = 1;
	else if (str[i] == '\"' && *dq == 1)
		*dq = 0;
	return (NULL);
}
char *cut_expander_loop_1(char *recup, char *res, t_env **env, int *f) {
    char *tmp_content;
    char *tmp_res;

    tmp_content = get_content_env(env, recup);
    if (!tmp_content) {
        tmp_content = ft_strdup("");  // Handle the case where environment variable is not found
    }

    if (!res) {
        res = ft_strdup(tmp_content);
    } else {
        tmp_res = ft_strjoin(res, tmp_content);
        free(res);
        res = tmp_res;
    }

    free(tmp_content);
    free(recup);
    recup = NULL;
    *f = 1;
    return res;
}


static char	*expander_loop_init(int *f, int *i)
{
	*i = -1;
	*f = 0;
	return (NULL);
}

char	*cut_expander_in_loop(char *str, int *i, char *recup)
{
	while (str && str[*i] && str[*i] != ' ' && valid_name(str[*i])
		&& str[*i] != '$')
		recup = reallocator(recup, str[(*i)++], 0);
	if (str[*i] == '$' || str[*i] == ' ' || !valid_name(str[*i]))
		(*i)--;
	return (recup);
}

char	*cut_expander_while_loop(char *str, t_env **env, int dq, int sq)
{
	int		f;
	int		i;
	char	*recup;
	char	*res;

	res = expander_loop_init(&f, &i);
	while (str && str[++i])
	{
		recup = recup_dq_sq_expander(str, i, &sq, &dq);
		if (str[i] == '$' && sq == 0 && ++i)
		{
			recup = cut_expander_in_loop(str, &i, recup);
			if (recup)
				res = cut_expander_loop_1(recup, res, env, &f);
		}
		else
		{
			f = 1;
			res = reallocator(res, str[i], 0);
		}
		if (!recup && f == 0)
			res = reallocator(res, str[i], 0);
		f = 0;
	}
	return (res);
}

char	*expander(char *str, t_env **env, int i, char *res)
{
	(void)i;
	(void)res;
	if (!str || !str[0])
		return (str);
	res = cut_expander_while_loop(str, env, 0, 0);
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



void	process_tok(t_token *tok, t_node *node, t_minishell *mini, int *i)
{
	char	*expanded_value;

	if (!node->args || *i >= node->arg_count)
		return ;
	if (node->args[*i])
	{
		free(node->args[*i]);
		node->args[*i] = NULL;
	}
	if (tok->sq == 1)
	{
		node->args[*i] = ft_strdup(tok->value);
		if (!node->args[*i])
		{
			clear_process(node, i);
			return ;
		}
		if (*i == 0)
			node->cmd = ft_strdup(node->args[*i]);
		(*i)++;
		return ;
	}
	expanded_value = expander(ft_strdup(tok->value), &mini->env, 0, NULL);
	if (!expanded_value)
	{
		clear_process(node, i);
		return ;
	}
	node->args[*i] = expanded_value;
	if (!node->args[*i])
	{
		clear_process(node, i);
		return ;
	}
	if (*i == 0)
		node->cmd = ft_strdup(node->args[*i]);
	(*i)++;
}

void	fill_args(t_token *tokens, t_node *node, t_minishell *mini)
{
	t_token	*tok;
	int		i;

	tok = tokens;
	if (!tokens || !node)
		return ;
	if (node->lonely_expansion == 1)
	{
		node->args[0] = get_expansion(mini, tok);
		node->cmd = get_expansion(mini, tok);
		node->args[1] = NULL;
		return ;
	}
	i = 0;
	while (tok)
	{
		if (tok->type == TOKEN_WORD && !tok->processed)
		{
			printf("tok value: %s\n", tok->value);
			process_tok(tok, node, mini, &i);
			if (!node->args)
				return ;
		}
		tok = tok->next;
	}
	node->args[i] = NULL;
}

void	set_filename(t_token **tokens, t_node *node)
{
	t_token	*tok;

	if (!tokens || !*tokens || !node)
		return ;
	tok = *tokens;
	count_heredocs(&tok, node);
	allocate_memory_for_limiter_hd(node);
	count_redir_in(&tok, node);
	allocate_memory_for_filename_in(node);
	count_redir_out(&tok, node);
	allocate_memory_for_filename_out(node);
	process_heredoc_tokens(*tokens, node);
	node->limiter_hd[node->limiter_hd_count] = NULL;
	process_filename_in(*tokens, node);
	process_filename_out(*tokens, node);
	node->filename_out[node->file_out_count] = NULL;
}

void	parse_tokens(t_token *tokens, t_node *node, t_minishell *mini)
{
	if (!tokens)
	{
		return ;
	}
	init_parsing(node);
	set_filename(&tokens, node);
	init_args(tokens, node);
	set_cmd(tokens, node);
	process_expansions(&tokens);
	update_tokens(&tokens, node);
	check_lonely_expansions(tokens, node);
	set_expansions(tokens, node);
	fill_args(tokens, node, mini);
}
