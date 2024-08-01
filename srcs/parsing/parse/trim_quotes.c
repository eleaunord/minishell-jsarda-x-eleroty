/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:14:52 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 16:44:26 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_closing_quote(char *str, int i, int option)
{
	if (option == 1)
	{
		while (str[i])
		{
			if (str[i] == '"')
				return (i);
			i++;
		}
	}
	else if (option == 2)
	{
		while (str[i])
		{
			if (str[i] == '\'')
				return (i);
			i++;
		}
	}
	return (-1);
}

char	*clear_quotes(char *str, int start, int end)
{
	if (end == -1)
		return (NULL);
	else
	{
		str = ft_trim(str, start, 1);
		str = ft_trim(str, end - 1, 1);
	}
	return (str);
}

int	remove_quotes_loop(int *in_dq, int *in_sq, char *str, int i)
{
	if (str[i] == '\'' && *in_sq == 0 && *in_dq == 0)
	{
		*in_sq = 1;
		return (i);
	}
	else if (str[i] == '\"' && *in_dq == 0 && *in_sq == 0)
	{
		*in_dq = 1;
		return (i);
	}
	return (0);
}

char	*strip_quotes(int in_dq, int in_sq, char *str, int i)
{
	int	start;
	int	end;

	while (str && str[i])
	{
		start = 0;
		end = -1;
		start = remove_quotes_loop(&in_dq, &in_sq, str, i);
		if (in_dq == 1 && in_sq == 0)
			end = find_closing_quote(str, i + 1, 1);
		if (in_sq == 1 && in_dq == 0)
			end = find_closing_quote(str, i + 1, 2);
		if (end != -1)
		{
			str = clear_quotes(str, start, end);
			if (!str)
				return (NULL);
			in_sq = 0;
			in_dq = 0;
			i = end - 2;
		}
		i++;
	}
	return (str);
}
