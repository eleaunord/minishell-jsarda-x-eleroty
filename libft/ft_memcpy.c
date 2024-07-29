/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:21:04 by jsarda            #+#    #+#             */
/*   Updated: 2023/11/15 13:53:02 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*des;
	unsigned const char	*s;

	des = dest;
	s = src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		des[i] = s[i];
		i++;
	}
	return (dest);
}
