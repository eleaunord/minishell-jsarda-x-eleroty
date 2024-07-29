/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:07:27 by jsarda            #+#    #+#             */
/*   Updated: 2023/11/16 17:43:31 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len(int n)
{
	int	i;

	i = 0;
	if (n < 1)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		i;
	long	nbr;

	i = 0;
	nbr = n;
	len = n_len(n);
	res = malloc(sizeof(char) * (len) + 1);
	if (!res)
		return (NULL);
	if (nbr < 0)
	{
		res[i] = '-';
		nbr = -nbr;
		i++;
	}
	res[len] = '\0';
	len--;
	while (len >= i)
	{
		res[len--] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (res);
}
