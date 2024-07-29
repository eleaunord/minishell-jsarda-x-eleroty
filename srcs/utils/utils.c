/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/07/04 12:29:13 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/09 17:22:49 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strslen_tab_until(char **tab, int pos)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tab[i] && i <= pos)
	{
		len += ft_strlen(tab[i]);
		i++;
	}
	return (len - ft_strlen(tab[i - 1]) + 1);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_erase_in_tab(char **tab, int pos, int pos2)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(sizeof(char *) * (ft_tablen(tab)));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (i != pos && i != pos2)
			res[j++] = ft_strdup(tab[i]);
		i++;
	}
	res[j] = 0;
	freetab(tab);
	return (res);
}

size_t	count_args(char **args)
{
	size_t	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

char	*ft_erase(char *str, int pos, int len)
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
