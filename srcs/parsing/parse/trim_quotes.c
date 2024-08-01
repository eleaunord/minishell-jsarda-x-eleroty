/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:14:52 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 15:15:30 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_trim(char *str, int pos, int len)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * ((ft_strlen(str) - len) + 20));
	if (!res)
		free(NULL);
	ft_bzero(res, ft_strlen(str) - len + 20);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (i == pos)
			i += len;
		if ((size_t)i >= ft_strlen(str))
			break ;
		res[j] = str[i];
		j++;
	}
	free(str);
	res[j] = 0;
	return (res);
}

int	recup_second_quote(char *str, int i, int mode)
{
	if (mode == 1)
	{
		while (str[i])
		{
			if (str[i] == '"')
				return (i);
			i++;
		}
	}
	else if (mode == 2)
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
char	*cut_delete_quote(char *str, int pos1, int pos2)
{
	if (pos2 == -1)
		return (NULL);
	else
	{
		str = ft_trim(str, pos1, 1);
		str = ft_trim(str, pos2 - 1, 1);
	}
	return (str);
}
int	cut_delete_quote_loop(char *str, int i, int *dq, int *sq)
{
	if (str[i] == '\'' && *sq == 0 && *dq == 0)
	{
		*sq = 1;
		return (i);
	}
	else if (str[i] == '\"' && *dq == 0 && *sq == 0)
	{
		*dq = 1;
		return (i);
	}
	return (0);
}
char	*delete_extra_quotes(char *str, int i, int dq, int sq)
{
	int	pos1;
	int	pos2;

	while (str && str[i])
	{
		pos1 = 0;
		pos2 = -1;
		pos1 = cut_delete_quote_loop(str, i, &dq, &sq);
		if (dq == 1 && sq == 0)
			pos2 = recup_second_quote(str, i + 1, 1);
		if (sq == 1 && dq == 0)
			pos2 = recup_second_quote(str, i + 1, 2);
		if (pos2 != -1)
		{
			str = cut_delete_quote(str, pos1, pos2);
			if (!str)
				return (NULL);
			sq = 0;
			dq = 0;
			i = pos2 - 2;
		}
		i++;
	}
	return (str);
} 