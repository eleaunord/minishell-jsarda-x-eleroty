/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:13:23 by jsarda            #+#    #+#             */
/*   Updated: 2023/11/15 16:08:14 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	size_total;

	if (!nmemb || !size)
		return (malloc(1));
	if (__SIZE_MAX__ / nmemb < size)
		return (NULL);
	size_total = nmemb * size;
	res = malloc(size_total);
	if (!res)
		return (NULL);
	ft_bzero(res, size_total);
	return (res);
}
