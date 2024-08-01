/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:15:47 by eleroty           #+#    #+#             */
/*   Updated: 2024/08/01 14:16:24 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *res, char c, int i)
{
	char	*copy;

	copy = NULL;
	if (!res)
	{
		res = malloc(2);
		res[0] = c;
		res[1] = 0;
		return (res);
	}
	if (res)
	{
		copy = ft_strdup(res);
		free(res);
	}
	res = malloc(sizeof(char) * (ft_strlen(copy) + 2));
	while (copy && copy[i])
	{
		res[i] = copy[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = 0;
	free(copy);
	return (res);
}
