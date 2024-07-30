/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleroty <eleroty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:13:32 by juliensarda       #+#    #+#             */
/*   Updated: 2024/07/30 18:00:53 by eleroty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier(const char *name)
{
	int	i;

	i = 0;
	if (!name[0])
		return (0);
	if (name[0] >= '0' && name[0] <= '9')
		return (0);
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A'
					&& name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9')
				|| (name[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}

static const char	*trim(const char *str)
{
	while (*str && (*str == 32 || (*str >= 8 && *str <= 13)))
		str++;
	return (str);
}

unsigned long long int	overflow_manager(unsigned long long int nb, int sign,
		int *overflow)
{
	if (sign == -1)
	{
		if (nb > (unsigned long long)LLONG_MAX + 1)
			*overflow = 1;
		return ((unsigned long long)(-((long long)nb)));
	}
	else
	{
		if (nb > (unsigned long long)LLONG_MAX)
			*overflow = 1;
		return (nb);
	}
}

unsigned long long int	ft_atoll(const char *str, int *overflow)
{
	int						i;
	int						sign;
	unsigned long long int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	*overflow = 0;
	str = trim(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > (ULLONG_MAX - (str[i] - '0')) / 10)
		{
			*overflow = 1;
			return (0);
		}
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (overflow_manager(nb, sign, overflow));
}
