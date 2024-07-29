/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <jtaravel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:08:04 by jtaravel          #+#    #+#             */
/*   Updated: 2024/07/22 17:02:44 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_syntax_struct(t_s *s)
{
	s->dq_opened = 0;
	s->sq_opened = 0;
}

void	check_sq_dq(t_s *s_s, char c)
{
	if (c == '\'' && s_s->dq_opened == 0)
	{
		if (s_s->sq_opened == 0)
			s_s->sq_opened = 1;
		else
			s_s->sq_opened = 0;
	}
	if (c == '"' && s_s->sq_opened == 0)
	{
		if (s_s->dq_opened == 0)
			s_s->dq_opened = 1;
		else
			s_s->dq_opened = 0;
	}
}

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
