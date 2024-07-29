/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:38:30 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 11:38:44 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new_string;

	new_string = malloc(sizeof(char) * (n + 1));
	if (!new_string)
		return (0);
	ft_strlcpy(new_string, s, (n + 1));
	return (new_string);
}
