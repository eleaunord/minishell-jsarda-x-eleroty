/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:41:05 by jsarda            #+#    #+#             */
/*   Updated: 2023/11/15 13:53:33 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned char		*d;
	unsigned const char	*s;

	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
		while (n-- > 0)
			d[n] = s[n];
	else
	{
		i = -1;
		while (++i < (int)n)
			d[i] = s[i];
	}
	return (dest);
}
