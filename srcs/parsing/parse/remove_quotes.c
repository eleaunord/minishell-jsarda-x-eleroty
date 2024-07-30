/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:14:54 by eleroty           #+#    #+#             */
/*   Updated: 2024/07/30 13:20:55 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_variables(t_rem_quotes *data, char *word)
{
	data->i = -1;
	data->j = 0;
	data->quote = 0;
	data->len = ft_strlen(word);
	data->result = (char *)malloc(data->len + 1);
	if (!data->result)
		return ;
}

static int	process_single_quotes(const char *word, t_rem_quotes *data)
{
	while (word[++(data->i)] != '\'' && data->i < data->len)
	{
		data->result[data->j++] = word[data->i];
	}
	return (data->j);
}

char	*remove_quotes_from_word(char *word)
{
	t_rem_quotes	data;

	if (!word)
		return (NULL);
	init_variables(&data, word);
	while (++data.i < data.len)
	{
		if (word[data.i] == '\'' && data.quote == 0)
			data.j = process_single_quotes(word, &data);
		else if (word[data.i] == '"' && data.quote == 0)
			data.quote = '"';
		else if (word[data.i] == '"' && data.quote == '"')
			data.quote = 0;
		else if (data.quote == '"' && (word[data.i] == '\\'
				|| word[data.i] == '$' || word[data.i] == '`'))
			data.result[data.j++] = word[data.i];
		else
			data.result[data.j++] = word[data.i];
	}
	data.result[data.j] = '\0';
	return (data.result);
}
